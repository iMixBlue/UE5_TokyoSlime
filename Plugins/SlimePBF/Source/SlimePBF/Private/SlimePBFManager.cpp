
#include "SlimePBFManager.h"
#include "Algo/Sort.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Runtime/Core/Public/Async/ParallelFor.h"
#include "SlimePBFTypes.h" 
#include "ProceduralMeshComponent.h"
#include "DrawDebugHelpers.h"

USlimePBFManager::USlimePBFManager()
{
}

USlimePBFManager::~USlimePBFManager()
{
}

void USlimePBFManager::InitializeSimulation(UWorld* InWorld)
{
    Particles.Reset();
    _colliderBuffer.Reset();

    Particles.SetNum(SlimePBFUtils::Num);
    ParticlesTemp.SetNum(SlimePBFUtils::Num);
    PosPredict.SetNum(SlimePBFUtils::Num);
    PosOld.SetNum(SlimePBFUtils::Num);
    LambdaBuffer.Init(0.0f, SlimePBFUtils::Num);
    VelocityBuffer.Init(FVector::ZeroVector, SlimePBFUtils::Num);
    VelocityTempBuffer.Init(FVector::ZeroVector, SlimePBFUtils::Num);
    Hashes.SetNum(SlimePBFUtils::Num);
    ExternalForce = FVector::ZeroVector;

    const int32 GridSize = SlimePBFUtils::Width;
    const int32 HalfGrid = GridSize / 2;

    const float SimScale = SlimePBFUtils::Scale;
    
    if (InWorld)
    {
        //锟斤拷取锟斤拷锟叫达拷锟斤拷 "SlimeCollider" 锟斤拷签锟斤拷 Actor
        TArray<AActor*> AllActors;
        UGameplayStatics::GetAllActorsWithTag(InWorld, TEXT("SlimeCollider"), AllActors);

        for (AActor* Actor : AllActors)
        {
            if (!Actor) continue;

            // 1. BoxComponent 
            TArray<UBoxComponent*> BoxComps;
            Actor->GetComponents<UBoxComponent>(BoxComps);
            for (UBoxComponent* Box : BoxComps)
            {
                FMyBoxCollider NewCollider;

                FTransform OriginalTransform = Box->GetComponentTransform();

                FVector SimLocation = OriginalTransform.GetLocation() * SlimePBFUtils::Scale;

                // GetScaledBoxExtent() 
                NewCollider.Extent = Box->GetScaledBoxExtent() * SlimePBFUtils::Scale;

                NewCollider.Transform = OriginalTransform;
                NewCollider.Transform.SetLocation(SimLocation);
                NewCollider.Transform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));

                NewCollider.InverseTransform = NewCollider.Transform.Inverse();

                _colliderBuffer.Add(NewCollider);
                //锟斤拷印锟斤拷始锟斤拷时锟斤拷谁撞锟斤拷
                /*UE_LOG(LogTemp, Warning, TEXT("Collider Added: Actor=[%s] SimCenter=%s Extent=%s"),
                    *Actor->GetName(),
                    *NewCollider.Transform.GetLocation().ToString(),
                    *NewCollider.Extent.ToString());*/
            }

            // 2. StaticMeshComponent 
            if (BoxComps.Num() == 0)
            {
                TArray<UStaticMeshComponent*> MeshComps;
                Actor->GetComponents<UStaticMeshComponent>(MeshComps);
                for (UStaticMeshComponent* SMC : MeshComps)
                {
                    if (!SMC || SMC->GetCollisionEnabled() == ECollisionEnabled::NoCollision) continue;

                    FVector Min, Max;
                    SMC->GetLocalBounds(Min, Max);
                    FVector ExtentLocal = (Max - Min) * 0.5f;
                    FVector CenterLocal = (Min + Max) * 0.5f;

                    FTransform CompTransform = SMC->GetComponentTransform();
                    FVector WorldCenter = CompTransform.TransformPosition(CenterLocal);
                    FVector ComponentScale = CompTransform.GetScale3D(); 

                    FVector SimExtent = ExtentLocal * ComponentScale.GetAbs() * SlimePBFUtils::Scale;

                    FMyBoxCollider NewCollider;
                    NewCollider.Transform = CompTransform;
                    NewCollider.Transform.SetLocation(WorldCenter * SlimePBFUtils::Scale);

                
                    NewCollider.Transform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));

                    NewCollider.Extent = SimExtent;
                    NewCollider.InverseTransform = NewCollider.Transform.Inverse();

                    _colliderBuffer.Add(NewCollider);
                }
            }
        }
    }

    //UE_LOG(LogTemp, Warning, TEXT("Collected Colliders = %d"), _colliderBuffer.Num());


    for (int32 i = 0; i < HalfGrid; i++)
    {
        for (int32 j = 0; j < GridSize; j++)
        {
            for (int32 k = 0; k < GridSize; k++)
            {
                int32 idx = i * GridSize * GridSize + j * GridSize + k;

                FSlimeParticle Particle;
                float scale = 1.0f;

                Particle.Position = FVector(
                    (k - HalfGrid)* scale,
                    (i - HalfGrid) * scale,
                    j * scale
                ) * 0.5f;
                
                Particle.ID = 0;

                Particles[idx] = Particle;
            }
        }
    }

    // --- Surface / Grid ---
    BoundsBuffer.SetNum(2);
    GridBuffer.SetNum(SlimePBFUtils::GridSize * SlimePBFUtils::GridNum);
    GridTempBuffer.SetNum(SlimePBFUtils::GridSize * SlimePBFUtils::GridNum);
    GridIDBuffer.SetNum(SlimePBFUtils::GridSize * SlimePBFUtils::GridNum);

    ComponentsBuffer.Reset();
    ComponentsBuffer.SetNum(16);
    // --- Controllers & Instances ---
    Controllers.Reset();
    // controller
    FSlimeParticleController DefaultController;
    DefaultController.Center = FVector::ZeroVector;
    DefaultController.Radius = 10.0f;
    DefaultController.Velocity = FVector::ZeroVector;
    DefaultController.Concentration = Concentration;
    Controllers.Add(DefaultController);

    SlimeInstances.Reset();
    FSlimeInstance newInstance;
    newInstance.Center = FVector::ZeroVector;
    newInstance.Pos = FVector::ZeroVector;
    newInstance.Dir = FVector::ZeroVector;
    newInstance.Radius = 1.0f;

    //SlimeInstances.Add(newInstance);
    //UE_LOG(LogTemp, Warning, TEXT("InstanceCount锟斤拷%d"), SlimeInstances.Num());
    //UE_LOG(LogTemp, Warning, TEXT("111"));

    InstancePool.Reset();
    ControlledInstance = 0;
    bConnect = false;

    // --- Bubbles ---
    BubblesBuffer.SetNum(SlimePBFUtils::BubblesCount);
    BubblesPoolStack.Reset();
    for (int32 i = 0; i < SlimePBFUtils::BubblesCount; ++i)
    {
        BubblesBuffer[i].LifeTime = -1.0f;
        BubblesPoolStack.Add(i);
    }

    BubblesNum = 0;

    GMatrixBuffer.SetNum(SlimePBFUtils::Num);
    VertPos = {
        FIntVector{0, 0, 0},
        FIntVector{1, 0, 0},
        FIntVector{1, 1, 0},
        FIntVector{0, 1 ,0},
        FIntVector{0, 0, 1},
        FIntVector{1, 0, 1},
        FIntVector{1, 1, 1},
        FIntVector{0, 1, 1},
    };

    EdgeVert =
    {
        FIntVector2{0, 1},
        FIntVector2{1, 2},
        FIntVector2{2, 3},
        FIntVector2{0, 3},
        FIntVector2{4, 5},
        FIntVector2{5, 6},
        FIntVector2{6, 7},
        FIntVector2{4, 7},
        FIntVector2{0, 4},
        FIntVector2{1, 5},
        FIntVector2{2, 6},
        FIntVector2{3, 7},
    };
    _cubeEdgeFlags = SlimePBFUtils::CubeEdgeFlags;
    _triangleVertCountTable = SlimePBFUtils::TriangleVertCountTable;
    _triangleConnectionTable = SlimePBFUtils::TriangleConnectionTable;

    bInitialized = true;
}
void USlimePBFManager::OnKeyP()
{
    bConnect = true;
}
void USlimePBFManager::OnKeyR()
{

}

// Eigen Decomposition (Jacobi)  
struct FMatrix3x3
{
    float m[3][3];

    FORCEINLINE FVector operator*(const FVector& v) const
    {
        return FVector(
            m[0][0] * v.X + m[0][1] * v.Y + m[0][2] * v.Z,
            m[1][0] * v.X + m[1][1] * v.Y + m[1][2] * v.Z,
            m[2][0] * v.X + m[2][1] * v.Y + m[2][2] * v.Z
        );
    }
};

static void JacobiEigenDecomposition(
    const FMatrix3x3& A,
    FVector& OutEigenValues,
    FMatrix3x3& OutEigenVectors,
    int MaxIters = 16
)
{
    OutEigenVectors = {};
    OutEigenVectors.m[0][0] = OutEigenVectors.m[1][1] = OutEigenVectors.m[2][2] = 1.0f;

    FMatrix3x3 D = A;

    for (int iter = 0; iter < MaxIters; iter++)
    {
        int p = 0, q = 1;
        float maxVal = FMath::Abs(D.m[p][q]);

        auto CheckMax = [&](int i, int j)
            {
                float v = FMath::Abs(D.m[i][j]);
                if (v > maxVal)
                {
                    maxVal = v;
                    p = i; q = j;
                }
            };

        CheckMax(0, 2);
        CheckMax(1, 2);

        if (maxVal < 1e-6f) break;

        float app = D.m[p][p];
        float aqq = D.m[q][q];
        float apq = D.m[p][q];

        float phi = 0.5f * FMath::Atan2(2.0f * apq, aqq - app);
        float c = FMath::Cos(phi);
        float s = FMath::Sin(phi);

        for (int i = 0; i < 3; i++)
        {
            float dpi = D.m[i][p];
            float dqi = D.m[i][q];
            D.m[i][p] = c * dpi - s * dqi;
            D.m[i][q] = s * dpi + c * dqi;
        }

        for (int i = 0; i < 3; i++)
        {
            float dip = D.m[p][i];
            float diq = D.m[q][i];
            D.m[p][i] = c * dip - s * diq;
            D.m[q][i] = s * dip + c * diq;
        }

        for (int i = 0; i < 3; i++)
        {
            float vip = OutEigenVectors.m[i][p];
            float viq = OutEigenVectors.m[i][q];
            OutEigenVectors.m[i][p] = c * vip - s * viq;
            OutEigenVectors.m[i][q] = s * vip + c * viq;
        }
    }

    OutEigenValues = FVector(D.m[0][0], D.m[1][1], D.m[2][2]);
}

void USlimePBFManager::UpdateSimulation()
{
    if (!bInitialized) return;
        Lut.Empty();
        ApplyForces();
        BuildHash();
        Algo::Sort(Hashes, [](const FIntVector2& A, const FIntVector2& B){return A.X < B.X;});
        BuildLut();
        BuildShuffle();
        ComputeLambda();
        ComputeDeltaPos();
        UpdateParticles();
        ApplyViscosity();
}

// Simulation Start
void USlimePBFManager::ApplyForces()
{
    ParallelFor(
        Particles.Num(),
        [&](int32 Index)
        {
            FSlimeParticle& Particle = Particles[Index];

            FVector Velocity = VelocityBuffer[Index] * 0.99f + FVector(0, 0, Gravity) * SlimePBFUtils::DeltaTime;
            if (Particle.ID >= 0 && Particle.ID < Controllers.Num()) {
                FSlimeParticleController Controller = Controllers[Particle.ID];
                FVector ToCenter = (Controller.Center + FVector(0, 0, Controller.Radius * 0.05f)) - Particle.Position;
                float len = ToCenter.Size();
                
                float EffectiveLen = FMath::Min(len, Controller.Radius);

                if (len < Controller.Radius * 1.0f)
                {
                    Velocity = FMath::Lerp(Controller.Velocity, Velocity, FMath::Lerp(1.0f, len * 0.1f, Controller.Concentration * 0.002f));
                    Velocity += Controller.Concentration * SlimePBFUtils::DeltaTime * FMath::Min(1.0f, len) * ToCenter.GetSafeNormal(1.e-4f);
                }
            }
            
            Particle.Position += Velocity * SlimePBFUtils::PredictStep;
            ParticlesTemp[Index] = Particle;
            PosPredict[Index] = Particle.Position;
            VelocityBuffer[Index] = Velocity;
        }
    );
}

void USlimePBFManager::BuildHash()
{
    ParallelFor(Particles.Num(), [&](int32 Index) {
        FIntVector GridPos = SlimePBFUtils::GetCoord(PosPredict[Index]);
        int32 Hash = SlimePBFUtils::GetKey(GridPos);
        Hashes[Index] = FIntVector2(Hash, Index);
        });
}

void USlimePBFManager::BuildLut()
{
    if (Hashes.IsEmpty()) return;

    int32 CurrentKey = Hashes[0].X;
    int32 Start = 0;

    for (int32 i = 1; i < Hashes.Num(); ++i)
    {
        if (Hashes[i].X == CurrentKey) continue;
        if (!Lut.Contains(CurrentKey))
        {
            Lut.Add(CurrentKey, FIntVector2(Start, i));
        }
        CurrentKey = Hashes[i].X;
        Start = i;
    }
    if (!Lut.Contains(CurrentKey))
    {
        Lut.Add(CurrentKey, FIntVector2(Start, Hashes.Num()));
    }
}

void USlimePBFManager::BuildShuffle()
{
    ParallelFor(Particles.Num(), [&](int32 Index) {
        int32 id = Hashes[Index].Y;
        PosPredict[Index] = ParticlesTemp[id].Position;
        PosOld[Index] = Particles[id].Position;
        VelocityTempBuffer[Index] = VelocityBuffer[id];
        });
}

void USlimePBFManager::ComputeLambda()
{
    ParallelFor(Particles.Num(), [&](int32 Index) {
        const FVector& Pos = PosPredict[Index]; 
        FIntVector Coord = SlimePBFUtils::GetCoord(Pos);
        float rho = 0.0f;
        FVector grad_i = FVector::ZeroVector;
        float sigmaGrad = 0.0f;

        for (int32 dz = -1; dz <= 1; ++dz)
        {
            for (int32 dy = -1; dy <= 1; ++dy)
            {
                for (int32 dx = -1; dx <= 1; ++dx)
                {
                    FIntVector NeighborCoord = Coord + FIntVector(dx, dy, dz);
                    int32 Key = SlimePBFUtils::GetKey(NeighborCoord);
                    FIntVector2* RangePtr = Lut.Find(Key);
                    if (!RangePtr) continue;

                    FIntVector2 Range = *RangePtr;  
                    for (int32 j = Range.X; j < Range.Y; j++)
                    {
                        if (Index == j) continue;

                        FVector Dir = Pos - PosPredict[j];
                        float R2 = Dir.SizeSquared();
                        if (R2 >= SlimePBFUtils::h2) continue;

                        float R = FMath::Sqrt(R2);
                        rho += SlimePBFUtils::SmoothingKernelPoly6(R2) / SlimePBFUtils::TargetDensity;
                        FVector grad_j = SlimePBFUtils::DerivativeSpikyPow3(R) / SlimePBFUtils::TargetDensity * Dir.GetSafeNormal();
                        sigmaGrad += grad_j.SizeSquared();
                        grad_i += grad_j;
                    }
                }
            }
        }

        sigmaGrad += FVector::DotProduct(grad_i, grad_i);
        float c = FMath::Max(-0.2f, rho / SlimePBFUtils::TargetDensity - 1.0f);
        LambdaBuffer[Index] = -c / (sigmaGrad + 1e-5f);
        });
}

void USlimePBFManager::ComputeDeltaPos()
{
    const float TensileDq = 0.25f * SlimePBFUtils::h;
    //const float TensileK = 0.1f;
    const float TensileK = 0.08f;

    ParallelFor(Particles.Num(), [&](int32 Index) {
        const FVector& Pos = PosPredict[Index]; 
        FVector dp = FVector::ZeroVector;
        float W_dp = SlimePBFUtils::SmoothingKernelPoly6(TensileDq * TensileDq);  //W(r,h)

        float lambda = LambdaBuffer[Index];
        FIntVector coord = SlimePBFUtils::GetCoord(Pos);

        for (int32 dz = -1; dz <= 1; ++dz)
        {
            for (int32 dy = -1; dy <= 1; ++dy)
            {
                for (int32 dx = -1; dx <= 1; ++dx)
                {
                    FIntVector NeighborCoord = coord + FIntVector(dx, dy, dz);
                    int32 Key = SlimePBFUtils::GetKey(NeighborCoord);

                    FIntVector2* RangePtr = Lut.Find(Key);
                    if (!RangePtr) continue;

                    FIntVector2 Range = *RangePtr;  
                    for (int32 j = Range.X; j < Range.Y; j++)
                    {
                        if (Index == j) continue;

                        FVector Dir = Pos - PosPredict[j];
                        float R2 = FVector::DotProduct(Dir, Dir);
                        if (R2 > SlimePBFUtils::h2) continue;

                        float R = FMath::Sqrt(R2);
                        FVector w_spiky = SlimePBFUtils::SpikyKernelPow3(R) * Dir.GetSafeNormal(); //锟斤拷锟斤拷 Spiky 锟剿猴拷锟斤拷锟斤拷锟捷讹拷 w_spiky锟斤拷 锟斤拷锟节硷拷锟斤拷压锟斤拷锟斤拷氐锟轿伙拷乒锟斤拷住锟?
                        float corr = SlimePBFUtils::SmoothingKernelPoly6(R2) / W_dp; //锟斤拷锟斤拷 Poly6 锟剿猴拷锟斤拷锟斤拷氐锟斤拷锟斤拷锟斤拷锟?corr锟斤拷 s_corr锟斤拷 锟斤拷锟斤拷 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷Tensile Instability 锟斤拷锟斤拷锟斤拷锟斤拷
                        float s_corr = -TensileK * corr * corr * corr * corr;
                        dp += (lambda + LambdaBuffer[j] + s_corr) * w_spiky;
                    }
                }
            }
        }

        dp /= SlimePBFUtils::TargetDensity; //TargetDensity锟斤拷p0(roll 0)

        Particles[Index].Position = Pos - dp;
        Particles[Index].ID = 0;
        });
}

void USlimePBFManager::UpdateParticles()
{
    const float SimGroundLevel = 0.05f;

    ParallelFor(Particles.Num(), [&](int32 Index) {
        FSlimeParticle& Particle = Particles[Index];
        FVector OldPos = PosOld[Index]; // Unity: float3 PosOld
        FVector NewPos = Particle.Position; // Unity: p.Position

        // --- 1. 锟斤拷锟斤拷约锟斤拷
        NewPos.Z = FMath::Max(SimGroundLevel, NewPos.Z);

        // --- 2. 锟斤拷撞锟斤拷循锟斤拷
        for (const FMyBoxCollider& box : _colliderBuffer)
        {
            // 锟斤拷为 UE5 锟斤拷 Box 锟斤拷锟斤拷转锟斤拷锟斤拷锟斤拷锟斤拷要转锟斤拷锟街诧拷锟秸间处锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷学锟较等硷拷锟斤拷AABB 锟斤拷锟斤拷
            FVector LocalPos = box.InverseTransform.TransformPosition(NewPos);

            // 锟街诧拷锟秸硷拷锟斤拷锟斤拷木锟斤拷锟?(0,0,0)锟斤拷锟斤拷锟斤拷 dir 锟斤拷锟斤拷 LocalPos
            FVector Vec = LocalPos.GetAbs();
            FVector BoxExtent = box.Extent;

            // 锟较革拷锟斤拷锟角凤拷锟斤拷全锟节猴拷锟斤拷锟节诧拷
            if (Vec.X < BoxExtent.X && Vec.Y < BoxExtent.Y && Vec.Z < BoxExtent.Z)
            {
                FVector Remain = BoxExtent - Vec;

                int32 Axis = 0; // 0=X, 1=Y, 2=Z
                float MinRemain = Remain.X;

                if (Remain.Y < MinRemain)
                {
                    MinRemain = Remain.Y;
                    Axis = 1;
                }

                if (Remain.Z < MinRemain)
                {
                    MinRemain = Remain.Z;
                    Axis = 2;
                }

                // 只锟斤拷锟斤拷锟斤拷锟斤拷歉锟斤拷锟斤拷频锟斤拷锟斤拷妫拷锟斤拷锟斤拷岵伙拷锟?

                // 锟斤拷取锟斤拷锟斤拷 math.sign(dir)
                float Sign = (Axis == 0) ? FMath::Sign(LocalPos.X) :
                    (Axis == 1) ? FMath::Sign(LocalPos.Y) :
                    FMath::Sign(LocalPos.Z);

                // 锟狡碉拷锟斤拷锟斤拷
                if (Axis == 0) LocalPos.X = Sign * BoxExtent.X;
                else if (Axis == 1) LocalPos.Y = Sign * BoxExtent.Y;
                else if (Axis == 2) LocalPos.Z = Sign * BoxExtent.Z;

                // 锟斤拷锟斤拷锟斤拷锟斤拷木植锟斤拷锟斤拷锟阶拷锟斤拷锟斤拷锟斤拷锟斤拷辏拷锟斤拷锟?NewPos
                // 锟斤拷锟斤拷锟斤拷一锟斤拷 collider 循锟斤拷锟酵伙拷使锟斤拷锟斤拷锟斤拷锟轿伙拷锟?
                NewPos = box.Transform.TransformPosition(LocalPos);
            }
        }

        Particle.Position = NewPos;
        PosPredict[Index] = NewPos;

        // --- 3. 锟劫度革拷锟斤拷 
        FVector Vel = (NewPos - OldPos) / SlimePBFUtils::DeltaTime;

        float Speed = Vel.Size();
         if (Speed > 30.0f)
         {
              Vel = Vel.GetSafeNormal() * 30.0f;
         }

        VelocityBuffer[Index] = Vel;
        Particles[Index] = Particle;
        });
}

void USlimePBFManager::ApplyViscosity()
{
    ParallelFor(Particles.Num(), [&](int32 Index) {
        const FVector& Pos = PosPredict[Index];
        FIntVector Coord = SlimePBFUtils::GetCoord(Pos);
        FVector ViscosityForce = FVector::ZeroVector;
        FVector Vel = VelocityTempBuffer[Index];

        for (int32 dz = -1; dz <= 1; ++dz)
        {
            for (int32 dy = -1; dy <= 1; ++dy)
            {
                for (int32 dx = -1; dx <= 1; ++dx)
                {
                    FIntVector NeighborCoord = Coord + FIntVector(dx, dy, dz);
                    int32 Key = SlimePBFUtils::GetKey(NeighborCoord);
                    FIntVector2* RangePtr = Lut.Find(Key);
                    if (!RangePtr) continue;

                    FIntVector2 Range = *RangePtr;
                    for (int32 j = Range.X; j < Range.Y; j++)
                    {
                        if (Index == j) continue;

                        FVector Dir = Pos - PosPredict[j];
                        float R2 = Dir.SizeSquared();
                        if (R2 > SlimePBFUtils::h2) continue;

                        ViscosityForce += (VelocityTempBuffer[j] - Vel) * SlimePBFUtils::SmoothingKernelPoly6(R2);
                    }
                }
            }
        }
        VelocityBuffer[Index] = Vel + ViscosityForce / SlimePBFUtils::TargetDensity * ViscosityStrength * SlimePBFUtils::DeltaTime;
        });
}
// Simulation End

//Surface Start
 void USlimePBFManager::UpdateSurface()
{
    const int32 ParticleNum = Particles.Num();
    USlimePBFManager::ComputeMeanPos();
    USlimePBFManager::ComputeCovariance();
    USlimePBFManager::CalcBounds();
    // block 锟斤拷锟斤拷
    //GridLut锟斤拷锟斤拷诤锟斤拷锟斤拷锟?
    const float BlockSize = SlimePBFUtils::CellSize * 4.0f;
    auto FloorToBlock = [BlockSize](float v)
        {
            return FMath::FloorToFloat(v / BlockSize) * BlockSize;
        };
    auto CeilToBlock = [BlockSize](float v)
        {
            return FMath::CeilToFloat(v / BlockSize) * BlockSize;
        };

    MinPos = FVector(
        FloorToBlock(BoundsBuffer[0].X),
        FloorToBlock(BoundsBuffer[0].Y),
        FloorToBlock(BoundsBuffer[0].Z));

    MaxPos = FVector(
        CeilToBlock(BoundsBuffer[1].X),
        CeilToBlock(BoundsBuffer[1].Y),
        CeilToBlock(BoundsBuffer[1].Z));

    USlimePBFManager::ClearGrid();
    USlimePBFManager::AllocateBlock();
    USlimePBFManager::ColorBlock();
    USlimePBFManager::DensityProjectionParallel();
    USlimePBFManager::GridBlur();
    USlimePBFManager::MarchingCubesParallel();
    USlimePBFManager::ConnectComponentBlock();
    USlimePBFManager::ParticleIDParallel();
    if (ComponentsBuffer.Num() > 0)
        bReadyForControl = true;
}
//render
void USlimePBFManager::ComputeMeanPos() //锟斤拷锟斤拷锟斤拷斯平锟斤拷 
{
    const int32 ParticleNum = Particles.Num();
    
    ParallelFor(ParticleNum, [&](int32 Index)
        {
            const FSlimeParticle& P = Particles[Index];
            const FVector Pos = P.Position;
            const FIntVector Coord = SlimePBFUtils::GetCoord(Pos);

            float Rho = 0.0f;
            FVector PosSum = FVector::ZeroVector;

            for (int32 dz = -1; dz <= 1; ++dz)
                for (int32 dy = -1; dy <= 1; ++dy)
                    for (int32 dx = -1; dx <= 1; ++dx)
                    {
                        const int32 Key = SlimePBFUtils::GetKey(Coord + FIntVector(dx, dy, dz));

                        if (FIntVector2* RangePtr = Lut.Find(Key))
                        {
                            const FIntVector2 Range = *RangePtr;
                            for (int32 j = Range.X; j < Range.Y; j++)
                            {
                                const FVector NeighborPos = Particles[j].Position;
                                const FVector Dir = Pos - NeighborPos;
                                const float   R2 = Dir.SizeSquared();
                                if (R2 > SlimePBFUtils::h2) continue;

                                const float W = SlimePBFUtils::SmoothingKernelPoly6(R2);
                                Rho += W;
                                PosSum += NeighborPos * W;
                            }
                        }
                    }

            FSlimeParticle Smoothed = P;
            Smoothed.Position = (Rho > 1e-5f) ? (PosSum / Rho) : Pos;
            ParticlesTemp[Index] = Smoothed;
        });
}
void USlimePBFManager::ComputeCovariance()
{
    const int32 ParticleNum = Particles.Num();

    ParallelFor(ParticleNum, [&](int32 Index)
        {
            const FVector Pos = Particles[Index].Position;
            const FIntVector Coord = SlimePBFUtils::GetCoord(Pos);

            const FVector MeanPos = ParticlesTemp[Index].Position;  
            float Rho = 0.0f;
            FMatrix3x3 Cov = {};

            auto OutDot = [](const FVector& a, FMatrix3x3& M)
                {
                    M.m[0][0] += a.X * a.X;
                    M.m[0][1] += a.X * a.Y;
                    M.m[0][2] += a.X * a.Z;

                    M.m[1][0] += a.Y * a.X;
                    M.m[1][1] += a.Y * a.Y;
                    M.m[1][2] += a.Y * a.Z;

                    M.m[2][0] += a.Z * a.X;
                    M.m[2][1] += a.Z * a.Y;
                    M.m[2][2] += a.Z * a.Z;
                };

            for (int32 dz = -1; dz <= 1; dz++)
                for (int32 dy = -1; dy <= 1; dy++)
                    for (int32 dx = -1; dx <= 1; dx++)
                    {
                        const int32 Key = SlimePBFUtils::GetKey(Coord + FIntVector(dx, dy, dz));
                        FIntVector2* RangePtr = Lut.Find(Key);
                        if (!RangePtr) continue;

                        FIntVector2 Range = *RangePtr;
                        for (int32 j = Range.X; j < Range.Y; j++)
                        {
                            const FVector NeighborPos = Particles[j].Position;
                            FVector Dir = NeighborPos - MeanPos;

                            float R2 = Dir.SizeSquared();
                            if (R2 > SlimePBFUtils::h2) continue;

                            float W = SlimePBFUtils::SmoothingKernelPoly6(R2);
                            Rho += W;
                            OutDot(Dir, Cov);
                        }
                    }

            // Normalize
            if (Rho > 1e-5f)
            {
                for (int a = 0; a < 3; a++)
                    for (int b = 0; b < 3; b++)
                        Cov.m[a][b] /= Rho;
            }
            else
            {
                // Identity
                Cov = {};
                Cov.m[0][0] = Cov.m[1][1] = Cov.m[2][2] = 1.0f;
            }

            // 锟斤拷锟斤拷锟街斤拷玫锟斤拷锟斤拷煞锟?
            float Trace = Cov.m[0][0] + Cov.m[1][1] + Cov.m[2][2];
            float InvTrace = 3.0f / FMath::Max(Trace, 1e-6f);
            for (int a = 0; a < 3; a++)
                for (int b = 0; b < 3; b++)
                    Cov.m[a][b] *= InvTrace;

            // -------- Eigen decomposition --------
            FVector EigenVals;
            FMatrix3x3 V;
            JacobiEigenDecomposition(Cov, EigenVals, V);

            // -------- Clamp eigen values to prevent artifacts --------
            FVector LambdaClamped(
                1.0f / FMath::Max(EigenVals.X, 0.1f),
                1.0f / FMath::Max(EigenVals.Y, 0.1f),
                1.0f / FMath::Max(EigenVals.Z, 0.1f)
            );

            // -------- Reconstruct anisotropic matrix G = V * diag(lambda) * V^T --------
            FMatrix3x3 G = {};

            for (int r = 0; r < 3; r++)
                for (int c = 0; c < 3; c++)
                {
                    G.m[r][c] =
                        V.m[r][0] * LambdaClamped.X * V.m[c][0] +
                        V.m[r][1] * LambdaClamped.Y * V.m[c][1] +
                        V.m[r][2] * LambdaClamped.Z * V.m[c][2];
                }

            // Normalize again by trace
            Trace = G.m[0][0] + G.m[1][1] + G.m[2][2];
            InvTrace = 3.0f / FMath::Max(Trace, 1e-6f);

            for (int r = 0; r < 3; r++)
                for (int c = 0; c < 3; c++)
                    G.m[r][c] *= InvTrace;

            // -------- Store into 4x4 FMatrix (Unity style) --------
            FMatrix M;

            M.M[0][0] = G.m[0][0]; M.M[0][1] = G.m[0][1]; M.M[0][2] = G.m[0][2]; M.M[0][3] = 0;
            M.M[1][0] = G.m[1][0]; M.M[1][1] = G.m[1][1]; M.M[1][2] = G.m[1][2]; M.M[1][3] = 0;
            M.M[2][0] = G.m[2][0]; M.M[2][1] = G.m[2][1]; M.M[2][2] = G.m[2][2]; M.M[2][3] = 0;
            M.M[3][0] = 0;         M.M[3][1] = 0;         M.M[3][2] = 0;         M.M[3][3] = 1;

            GMatrixBuffer[Index] = M;
        });
}

void USlimePBFManager::CalcBounds()
{
    const int32 ParticleNum = Particles.Num();

    FVector Min(FLT_MAX, FLT_MAX, FLT_MAX);
    FVector Max(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    for (int32 i = 0; i < ParticleNum; ++i)
    {
        const FVector& Pos = ParticlesTemp[i].Position;
        Min.X = FMath::Min(Min.X, Pos.X);
        Min.Y = FMath::Min(Min.Y, Pos.Y);
        Min.Z = FMath::Min(Min.Z, Pos.Z);

        Max.X = FMath::Max(Max.X, Pos.X);
        Max.Y = FMath::Max(Max.Y, Pos.Y);
        Max.Z = FMath::Max(Max.Z, Pos.Z);
    }
    BoundsBuffer[0] = Min;
    BoundsBuffer[1] = Max;
    /*UE_LOG(LogTemp, Warning, TEXT("Bounds: Min=%s, Max=%s"),
        *BoundsBuffer[0].ToString(), *BoundsBuffer[1].ToString());*/
}

//Allocate
void USlimePBFManager::ClearGrid()
{
    const int32 GridTotal = GridBuffer.Num();
    ParallelFor(GridTotal, [&](int32 Index)
        {
            GridBuffer[Index] = 0.0f;
            GridIDBuffer[Index] = -1;
        });
}
void USlimePBFManager::AllocateBlock()
{
    const int32 ParticleNum = Particles.Num();
    GridLut.Empty();
    int32 Ptr = 0;

    for (int32 i = 0; i < ParticleNum; ++i)
    {
        const FVector RelativePos = ParticlesTemp[i].Position - MinPos;
        const FIntVector Coord(
            FMath::FloorToInt(RelativePos.X / SlimePBFUtils::CellSize),
            FMath::FloorToInt(RelativePos.Y / SlimePBFUtils::CellSize),
            FMath::FloorToInt(RelativePos.Z / SlimePBFUtils::CellSize));

        const FIntVector BlockMin = (Coord - FIntVector(2, 2, 2)) >> 2;
        const FIntVector BlockMax = (Coord + FIntVector(2, 2, 2)) >> 2;

        for (int32 bz = BlockMin.Z; bz <= BlockMax.Z; ++bz)
            for (int32 by = BlockMin.Y; by <= BlockMax.Y; ++by)
                for (int32 bx = BlockMin.X; bx <= BlockMax.X; ++bx)
                {
                    const FIntVector Key(bx, by, bz);
                    if (GridLut.Contains(Key)) continue;

                    const int32 Offset = Ptr * SlimePBFUtils::GridSize;
                    GridLut.Add(Key, Offset);
                    ++Ptr;
                    if (Ptr >= SlimePBFUtils::GridNum) break;
                }
    }
}
void USlimePBFManager::ColorBlock()
{
    //锟斤拷色锟斤拷锟叫ｏ拷锟斤拷时没锟斤拷实锟街ｏ拷锟皆猴拷锟斤拷锟斤拷
    const int32 ParticleNum = Particles.Num();
}
void USlimePBFManager::DensityProjectionParallel()
{
    BlockNum = GridLut.Num();
    TArray<FIntVector> Keys;
    GridLut.GetKeys(Keys);

    ParallelFor(BlockNum, [&](int32 BlockIndex)
        {
            const FIntVector Block = Keys[BlockIndex];
            const FIntVector BasePos = SlimePBFUtils::GetCoord(MinPos);
            const FIntVector BlockMinCoord = Block * 2 + BasePos;

            float BlockTemp[SlimePBFUtils::GridSize];
            for (int32 j = 0; j < SlimePBFUtils::GridSize; ++j)
                BlockTemp[j] = 0.0f;

            const int32 Offset = GridLut[Block];

            for (int32 z = -1; z < 3; ++z)
                for (int32 y = -1; y < 3; ++y)
                    for (int32 x = -1; x < 3; ++x)
                    {
                        const FIntVector NeighborCell = BlockMinCoord + FIntVector(x, y, z);
                        const int32 ParticleKey = SlimePBFUtils::GetKey(NeighborCell);

                        FIntVector2* RangePtr = Lut.Find(ParticleKey);
                        if (!RangePtr) continue;
                        const FIntVector2 Range = *RangePtr;

                        for (int32 j = Range.X; j < Range.Y; j++)
                        {
                            const FVector RelativePos = ParticlesTemp[j].Position - MinPos;

                            for (int32 gz = FMath::Max(0, z * 2 - 2); gz < FMath::Min(4, z * 2 + 4); ++gz)
                                for (int32 gy = FMath::Max(0, y * 2 - 2); gy < FMath::Min(4, y * 2 + 4); ++gy)
                                    for (int32 gx = FMath::Max(0, x * 2 - 2); gx < FMath::Min(4, x * 2 + 4); ++gx)
                                    {
                                        const FIntVector Coord = (Block << 2) + FIntVector(gx, gy, gz);
                                        const FVector CellCenter = (FVector(Coord) + FVector(0.5f)) * SlimePBFUtils::CellSize;
                                        FVector Dir = CellCenter - RelativePos;

                                        //dir = math.mul((float3x3)GMatrix[j], dir);
                                        Dir = GMatrixBuffer[j].TransformVector(Dir);

                                        const float R2 = Dir.SizeSquared();
                                        if (R2 > SlimePBFUtils::h2) continue;

                                        const float Density = SlimePBFUtils::SmoothingKernelPoly6(R2);
                                        const int32 LocalIndex = (gx & 3) + 4 * ((gy & 3) + 4 * (gz & 3));
                                        BlockTemp[LocalIndex] += Density;
                                    }
                        }
                    }

            for (int32 j = 0; j < SlimePBFUtils::GridSize; ++j)
                GridBuffer[Offset + j] = BlockTemp[j];
        });
}

//Blur
void USlimePBFManager::GridBlur()
{
    BlockNum = GridLut.Num();
    TArray<FIntVector> Keys;
    GridLut.GetKeys(Keys);

    GridTempBuffer = GridBuffer; 
    ParallelFor(BlockNum, [&](int32 Index)
        {
            const FIntVector Key = Keys[Index];
            if (!GridLut.Contains(Key)) return;

            float Block[6 * 6 * 6];
            for (int32 i = 0; i < 6 * 6 * 6; ++i) Block[i] = 0.0f;

            const FIntVector MinCoord = Key * 4 - FIntVector(1, 1, 1);

            auto GetLocalCoord = [](int32 Idx)->FIntVector {
                return FIntVector(Idx & 3, (Idx >> 2) & 3, (Idx >> 4) & 3);
                };
            auto GetBlockIndex = [](const FIntVector& C)->int32 {
                return C.X + 6 * (C.Y + 6 * C.Z);
                };

            for (int32 dz = -1; dz <= 1; ++dz)
                for (int32 dy = -1; dy <= 1; ++dy)
                    for (int32 dx = -1; dx <= 1; ++dx)
                    {
                        const FIntVector NKey = Key + FIntVector(dx, dy, dz);
                        const int32* NOffPtr = GridLut.Find(NKey);
                        if (!NOffPtr) continue;

                        const int32 NOff = *NOffPtr;
                        for (int32 j = 0; j < SlimePBFUtils::GridSize; j++)
                        {
                            const FIntVector Coord = (NKey << 2) + GetLocalCoord(j) - MinCoord;
                            if (Coord.X < 0 || Coord.Y < 0 || Coord.Z < 0 ||
                                Coord.X >= 6 || Coord.Y >= 6 || Coord.Z >= 6)
                                continue;

                            Block[GetBlockIndex(Coord)] = GridBuffer[NOff + j];
                        }
                    }

            const int32 Offset = GridLut[Key];
            for (int32 j = 0; j < SlimePBFUtils::GridSize; j++)
            {
                const FIntVector Coord = GetLocalCoord(j) + FIntVector(1, 1, 1);

                float Sum = 0.0f;
                float Weight = 0.0f;
                for (int32 dz = -1; dz <= 1; ++dz)
                    for (int32 dy = -1; dy <= 1; ++dy)
                        for (int32 dx = -1; dx <= 1; ++dx)
                        {
                            const FIntVector NCoord = Coord + FIntVector(dx, dy, dz);
                            const int32 Idx = GetBlockIndex(NCoord);
                            Sum += Block[Idx];
                            Weight += 1.0f - 0.5f * FVector(dx, dy, dz).Size();
                        }

                GridTempBuffer[Offset + j] = Sum / FMath::Max(Weight, 1e-5f);
            }
        });

    // Blur 锟斤拷锟叫达拷锟?GridBuffer
    GridBuffer = GridTempBuffer;
}

//Marching cubes
void USlimePBFManager::MarchingCubesParallel()
{
    if (!SurfaceMesh) return;

    auto GetBlockIndex = [](const FIntVector& Coord)->int32
        {  return Coord.X + 8 * (Coord.Y + 8 * Coord.Z); };

    auto ReadGrid = [&](const FIntVector& Coord, const float* Block)->float
        {
            FIntVector ClampedCoord(
                FMath::Clamp(Coord.X, 0, 7),
                FMath::Clamp(Coord.Y, 0, 7),
                FMath::Clamp(Coord.Z, 0, 7)
            );
            return Block[GetBlockIndex(ClampedCoord)];
        };

    auto GetLocalCoord = [](int32 Index) -> FIntVector {
        return FIntVector(
            Index & 3,
            (Index >> 2) & 3,
            (Index >> 4) & 3
        );
        };

    // 锟斤拷锟斤拷锟皆讹拷值锟斤拷锟斤拷锟节凤拷锟竭ｏ拷
    auto ReadBlockTrilinear = [&](const FVector& UVW, const float* Block)->float
        {
            // P000 锟斤拷锟斤拷 minCoord 为原锟斤拷木植锟斤拷锟斤拷辏拷锟轿拷锟斤拷悖?
            FIntVector P000(
                FMath::FloorToInt(UVW.X),
                FMath::FloorToInt(UVW.Y),
                FMath::FloorToInt(UVW.Z)
            );
            FIntVector P111 = P000 + FIntVector(1, 1, 1);
            FVector F = UVW - FVector(P000);

            // 锟斤拷取8锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷值
            float C000 = ReadGrid(P000, Block);
            float C100 = ReadGrid(FIntVector(P111.X, P000.Y, P000.Z), Block);
            float C010 = ReadGrid(FIntVector(P000.X, P111.Y, P000.Z), Block);
            float C110 = ReadGrid(FIntVector(P111.X, P111.Y, P000.Z), Block);
            float C001 = ReadGrid(FIntVector(P000.X, P000.Y, P111.Z), Block);
            float C101 = ReadGrid(FIntVector(P111.X, P000.Y, P111.Z), Block);
            float C011 = ReadGrid(FIntVector(P000.X, P111.Y, P111.Z), Block);
            float C111 = ReadGrid(P111, Block);

            // 锟斤拷锟斤拷锟皆诧拷值锟斤拷锟斤拷
            float C00 = FMath::Lerp(C000, C100, F.X);
            float C10 = FMath::Lerp(C010, C110, F.X);
            float C01 = FMath::Lerp(C001, C101, F.X);
            float C11 = FMath::Lerp(C011, C111, F.X);

            float C0 = FMath::Lerp(C00, C10, F.Y);
            float C1 = FMath::Lerp(C01, C11, F.Y);
            return FMath::Lerp(C0, C1, F.Z);
        };

    auto CalcNormal = [&](const FVector& pos, float* block) -> FVector
        {
            const FVector offset(1.f, 0.f, 0.f);

            float nx = ReadBlockTrilinear(pos - offset, block)
                - ReadBlockTrilinear(pos + offset, block);

            const FVector offset_yxz(0.f, 1.f, 0.f);
            float ny = ReadBlockTrilinear(pos - offset_yxz, block)
                - ReadBlockTrilinear(pos + offset_yxz, block);

            const FVector offset_yzx(0.f, 0.f, 1.f);
            float nz = ReadBlockTrilinear(pos - offset_yzx, block)
                - ReadBlockTrilinear(pos + offset_yzx, block);

            FVector n(nx, ny, nz);
            return n.GetSafeNormal();
        };

    BlockNum = GridLut.Num();
    TArray<FIntVector> Keys;
    GridLut.GetKeys(Keys);

    // -------- Pass 1: 统锟斤拷每锟斤拷 block 锟斤拷锟斤拷锟斤拷锟斤拷锟角讹拷锟斤拷锟斤拷
    TArray<int32> BlockVertPrefix;  // 锟斤拷锟斤拷 = BlockNum + 1锟斤拷锟斤拷锟揭伙拷锟斤拷锟?total
    BlockVertPrefix.SetNumZeroed(BlockNum + 1);

    ParallelFor(BlockNum, [&](int32 Index)
        {
            const FIntVector Key = Keys[Index];

            // 锟斤拷 8x8x8 block锟斤拷锟斤拷 Key 锟斤拷锟斤拷锟斤拷锟斤拷 26 锟斤拷锟节居革拷锟狡斤拷去
            float Block[512] = { 0.0f };

            const FIntVector MinCoord = (Key << 2) - FIntVector(2, 2, 2);

            for (int dz = -1; dz <= 1; ++dz)
                for (int dy = -1; dy <= 1; ++dy)
                    for (int dx = -1; dx <= 1; ++dx)
                    {
                        const FIntVector NKey = Key + FIntVector(dx, dy, dz);
                        const int32* OffPtr = GridLut.Find(NKey);
                        if (!OffPtr) continue;

                        const int32 NOff = *OffPtr;
                        for (int j = 0; j < SlimePBFUtils::GridSize; j++)
                        {
                            FIntVector C = (NKey * 4) + GetLocalCoord(j) - MinCoord;
                            if (C.X < 0 || C.Y < 0 || C.Z < 0 || C.X >= 8 || C.Y >= 8 || C.Z >= 8) continue;
                            Block[GetBlockIndex(C)] = GridTempBuffer[NOff + j];
                        }
                    }

            int32 VertCount = 0;

            // 锟斤拷锟斤拷锟节诧拷锟斤拷锟斤拷锟斤拷 (localCoord = 1..5)锟斤拷锟竭斤拷锟斤拷锟斤拷诰锟饺ワ拷锟?
            for (int z = 1; z < 6; z++)
                for (int y = 1; y < 6; y++)
                    for (int x = 1; x < 6; x++)
                    {
                        int32 result = 0;

                        FIntVector LocalCoord(x, y, z);
                        FIntVector Coord = LocalCoord + MinCoord;
                        FIntVector NKey = Coord >> 2;

                        // 锟斤拷 cube 锟斤拷锟斤拷 8x8x8 锟斤拷锟斤拷牵锟斤拷锟斤拷叶锟接︼拷锟绞?4x4x4 锟节匡拷锟斤拷冢锟斤拷锟斤拷锟斤拷锟斤拷员锟斤拷锟斤拷馗锟?
                        if ((x < 2 || y < 2 || z < 2 || x > 5 || y > 5 || z > 5) && GridLut.Contains(NKey))
                            continue;

                        // 锟斤拷锟斤拷 8 锟斤拷锟角碉拷锟斤拷值锟斤拷锟斤拷
                        for (int i = 0; i < 8; i++)
                        {
                            if (ReadGrid(LocalCoord + VertPos[i], Block) > Threshold)
                            {
                                result |= 1 << i;
                            }
                        }

                        VertCount += _triangleVertCountTable[result];
                    }

            BlockVertPrefix[Index] = VertCount;
        });

    // 锟斤拷前缀锟酵ｏ拷锟斤拷锟叫ｏ拷
    int32 Sum = 0;
    for (int32 i = 0; i < BlockVertPrefix.Num(); ++i)
    {
        const int32 C = BlockVertPrefix[i];
        BlockVertPrefix[i] = Sum;
        Sum += C;
    }
    const int32 TotalVerts = BlockVertPrefix[BlockNum];

    // -------- Pass 2: 锟斤拷锟斤拷写锟斤拷 锟斤拷锟斤拷/锟斤拷锟斤拷/锟斤拷锟斤拷 --------
    TArray<FVector> Vertices;      Vertices.SetNumUninitialized(TotalVerts);
    TArray<FVector> Normals;       Normals.SetNumUninitialized(TotalVerts);
    TArray<int32>   Indices;       Indices.SetNumUninitialized(TotalVerts);

    const float CellSize = SlimePBFUtils::CellSize; // 直锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷辏篗inPos + pos*CellSize
    ParallelFor(BlockNum, [&](int32 Index)
        {
                FIntVector key = Keys[Index];

                float weights[8];
                int32 indices[3];

                float block[512];
                FMemory::Memzero(block, sizeof(float) * 512);

                FIntVector minCoord = (key << 2) - FIntVector(2, 2, 2);

                // ----------------------------------------------------------------------

                for (int dz = -1; dz <= 1; ++dz)
                    for (int dy = -1; dy <= 1; ++dy)
                        for (int dx = -1; dx <= 1; ++dx)
                        {
                            FIntVector nKey = key + FIntVector(dx, dy, dz);

                            if (!GridLut.Contains(nKey))
                                continue;

                            int32 nOff = GridLut[nKey];

                            for (int j = 0; j < 64; j++)
                            {
                                FIntVector coord = (nKey * 4) + GetLocalCoord(j) - minCoord;

                                if (coord.X < 0 || coord.Y < 0 || coord.Z < 0 ||
                                    coord.X >= 8 || coord.Y >= 8 || coord.Z >= 8)
                                    continue;

                                block[GetBlockIndex(coord)] = GridTempBuffer[nOff + j];
                            }
                        }

                // ----------------------------------------------------------------------

                int32 offset = BlockVertPrefix[Index];

                for (int z = 1; z < 6; z++)
                    for (int y = 1; y < 6; y++)
                        for (int x = 1; x < 6; x++)
                        {
                            int32 result = 0;

                            FIntVector localCoord(x, y, z);
                            FIntVector coord = localCoord + minCoord;

                            FIntVector nKey(coord.X >> 2, coord.Y >> 2, coord.Z >> 2);

                            if ((localCoord.X < 2 || localCoord.Y < 2 || localCoord.Z < 2 ||
                                localCoord.X > 5 || localCoord.Y > 5 || localCoord.Z > 5)
                                && GridLut.Contains(nKey))
                                continue;

                            // ----- Read 8 corner weights --------------------------------------

                            for (int i = 0; i < 8; i++)
                            {
                                weights[i] = ReadGrid(localCoord + VertPos[i], block);

                                if (weights[i] > Threshold)
                                    result |= 1 << i;
                            }

                            // ----- Read triangle table ---------------------------------------

                            int32* line = _triangleConnectionTable.GetData() + result * 16;

                            if (line[0] < 0)
                                continue;

                            // ----- Build triangles -------------------------------------------

                            for (int i = 0; line[i] > -1 && i < 15; i += 3)
                            {
                                indices[0] = line[i];
                                indices[1] = line[i + 2];
                                indices[2] = line[i + 1];

                                for (int j = 0; j < 3; j++)
                                {
                                    FIntVector2 ev = EdgeVert[indices[j]];

                                    FIntVector v0 = VertPos[ev.X] + coord;
                                    FIntVector v1 = VertPos[ev.Y] + coord;

                                    float weight =
                                        (Threshold - weights[ev.X]) /
                                        (weights[ev.Y] - weights[ev.X]);

                                    FVector pos = FMath::Lerp(
                                        FVector(v0),
                                        FVector(v1),
                                        weight
                                    );

                                    FVector normal = -CalcNormal(pos - FVector(minCoord), block);

                                    // ----------- Write into preallocated buffers -----------------

                                    float Scale = SlimePBFUtils::InvScale;
                                    Vertices[offset] = (MinPos + pos * SlimePBFUtils::CellSize) * Scale;
                                    Normals[offset] = normal;
                                    Indices[offset] = offset;

                                    offset++;
                                }
                            }
                        }

                // ----------------------------------------------------------------------
        });

        //UE_LOG(LogTemp, Warning, TEXT("Vert 0: %s"), *Vertices[0].ToString());

        // 锟斤拷锟斤拷锟?ProceduralMesh
        //SurfaceMesh->ClearAllMeshSections();
        SurfaceMesh->CreateMeshSection_LinearColor(
            /*SectionIndex*/ 0,
            Vertices,
            Indices,
            Normals,
            /*UVs*/ TArray<FVector2D>(),
            /*VertexColors*/ TArray<FLinearColor>(),
            /*Tangents*/ TArray<FProcMeshTangent>(),
            /*bCreateCollision*/ false
        );

    SurfaceMesh->UpdateBounds();

    // 锟酵凤拷锟节达拷 (Unity Dispose)
    Vertices.Empty();
    Normals.Empty();
    Indices.Empty();
    BlockVertPrefix.Empty();
}

//CCA锟斤拷通锟斤拷指锟?
void USlimePBFManager::ConnectComponentBlock() //CCA 锟斤拷通锟斤拷指锟?
{
    TArray<FIntVector> Keys;
    GridLut.GetKeys(Keys);

    ComponentsBuffer.Reset();

    const int32 CellTotal = GridBuffer.Num();
    TArray<bool> Visited;
    Visited.Init(false, CellTotal);
    TArray<FIntVector> Stack;   // BFS stack
    Stack.SetNum(256);

    auto GetLocalCoord = [](int32 Idx)->FIntVector {
        return FIntVector(Idx & 3, (Idx >> 2) & 3, (Idx >> 4) & 3);
        };
    auto GetLocalIndex = [](const FIntVector& C)->int32 {
        return C.X + 4 * (C.Y + 4 * C.Z);
        };

    auto IsIdxValid = [&](int32 Idx, int32& OutIndex)->bool
        {
            if (Idx < 0 || Idx >= CellTotal) return false;
            if (Visited[Idx]) return false;
            Visited[Idx] = true;
            if (GridBuffer[Idx] < Threshold) return false;
            OutIndex = Idx;
            return true;
        };

    TArray<FIntVector> AllKeys = Keys;
    for (const FIntVector& Key : AllKeys)
    {
        const int32* OffsetPtr = GridLut.Find(Key);
        if (!OffsetPtr) continue;
        const int32 Offset = *OffsetPtr;

        for (int32 j = 0; j < SlimePBFUtils::GridSize; j++)
        {
            const FIntVector Coord = Key * 4 + GetLocalCoord(j);
            Stack.Reset();
            Stack.Add(Coord);

            FSlimeComponent Comp;
            Comp.ID = ComponentsBuffer.Num();
            Comp.Center = FVector::ZeroVector;
            Comp.BoundsMin = FVector(FLT_MAX, FLT_MAX, FLT_MAX);
            Comp.BoundsMax = FVector(-FLT_MAX, -FLT_MAX, -FLT_MAX);
            Comp.CellCount = 0;

            FVector PosSum = FVector::ZeroVector;

            while (Stack.Num() > 0)
            {
                FIntVector Cur = Stack[0];
                Stack.RemoveAtSwap(0);
                const FIntVector Key3 = Cur >> 2;

                const int32* OffPtr = GridLut.Find(Key3);
                if (!OffPtr) continue;
                const int32 Off = *OffPtr;
                const int32 LocalIdx = GetLocalIndex(SlimePBFUtils::Mod4(Cur));
                int32 Idx = 0;
                if (!IsIdxValid(Off + LocalIdx, Idx)) continue;
                GridIDBuffer[Off + LocalIdx] = ComponentsBuffer.Num();

                Comp.CellCount++;
                const FVector CellCenter = FVector(Cur) + FVector(0.5f);
                PosSum += CellCenter;
                Comp.BoundsMin.X = FMath::Min(Comp.BoundsMin.X, CellCenter.X);
                Comp.BoundsMin.Y = FMath::Min(Comp.BoundsMin.Y, CellCenter.Y);
                Comp.BoundsMin.Z = FMath::Min(Comp.BoundsMin.Z, CellCenter.Z);

                Comp.BoundsMax.X = FMath::Max(Comp.BoundsMax.X, CellCenter.X);
                Comp.BoundsMax.Y = FMath::Max(Comp.BoundsMax.Y, CellCenter.Y);
                Comp.BoundsMax.Z = FMath::Max(Comp.BoundsMax.Z, CellCenter.Z);

                // 6 锟节斤拷
                /*Stack.Add(Cur + FIntVector(1, 0, 0));
                Stack.Add(Cur - FIntVector(1, 0, 0));
                Stack.Add(Cur + FIntVector(0, 1, 0));
                Stack.Add(Cur - FIntVector(0, 1, 0));
                Stack.Add(Cur + FIntVector(0, 0, 1));
                Stack.Add(Cur - FIntVector(0, 0, 1));*/
                // 26-锟斤拷锟斤拷锟斤拷锟斤拷
                for (int32 dz = -1; dz <= 1; dz++)
                {
                    for (int32 dy = -1; dy <= 1; dy++)
                    {
                        for (int32 dx = -1; dx <= 1; dx++)
                        {
                            if (dx == 0 && dy == 0 && dz == 0) continue; // 锟斤拷锟斤拷锟皆硷拷

                            FIntVector Neighbor = Cur + FIntVector(dx, dy, dz);
                            Stack.Add(Neighbor);
                        }
                    }
                }
            }

            if (Comp.CellCount > 0)
            {
                Comp.Center = (Comp.BoundsMin + Comp.BoundsMax) * 0.5f;
                ComponentsBuffer.Add(Comp);
            }
        }
    }
    Stack.Empty();
    Visited.Empty();
}
void USlimePBFManager::ParticleIDParallel()
{
    const int32 ParticleNum = Particles.Num();
    auto GetLocalIndex = [](const FIntVector& C)->int32 {
        return C.X + 4 * (C.Y + 4 * C.Z);
        };

    ParallelFor(ParticleNum, [&](int32 Index)
        {
            FSlimeParticle P = Particles[Index];
            const FVector RelativePos = P.Position - MinPos;
            const FIntVector Coord(
                FMath::FloorToInt(RelativePos.X / SlimePBFUtils::CellSize),
                FMath::FloorToInt(RelativePos.Y / SlimePBFUtils::CellSize),
                FMath::FloorToInt(RelativePos.Z / SlimePBFUtils::CellSize));

            const FIntVector Key = Coord >> 2;

            if (const int32* OffsetPtr = GridLut.Find(Key))
            {
                const int32 Offset = *OffsetPtr;
                const int32 LocalIdx = GetLocalIndex(SlimePBFUtils::Mod4(Coord));
                P.ID = GridIDBuffer[Offset + LocalIdx];
            }
            else
            {
                P.ID = 0;
            }

            Particles[Index] = P;
        });
}

//Surface End

//Control Start
void USlimePBFManager::UpdateMainControllerVelocity(FVector newVelocity)
{
    MainControllerVelocity = newVelocity * 0.1f;
}
void USlimePBFManager::UpdateMainControllerPosition(FVector newPos) {
    MainControllerPosition = newPos * 0.1f;
}
void USlimePBFManager::UpdateControl()
{
    if (!bReadyForControl)
        return;
    Controllers.Reset();
    //UE_LOG(LogTemp, Warning, TEXT("ComponentsBuffer: %d"), ComponentsBuffer.Num());
    // 1. 每锟斤拷 Component 锟斤拷锟斤拷一锟斤拷 Controller
    for (const FSlimeComponent& Comp : ComponentsBuffer)
    {
        const FVector Extent = Comp.BoundsMax - Comp.Center;
        const float Radius = FMath::Max(
            1.0f,
           (Extent.X + Extent.Y + Extent.Z) * SlimePBFUtils::CellSize * 0.6f);

        FVector Center = MinPos + Comp.Center * SlimePBFUtils::CellSize;
        //UE_LOG(LogTemp, Warning, TEXT("Extent锟斤拷%s"), *Extent.ToString());
        // 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷抬一锟斤拷
       if (Extent.Z < 3.0f) 
        {
           Center.Z += Extent.Z * SlimePBFUtils::Scale * SlimePBFUtils::CellSize;
        }
        // 指锟斤拷锟斤拷锟斤拷锟狡讹拷锟斤拷

       FVector ToMain = 5.0f *
           (MainControllerPosition - Center).GetSafeNormal(0.0001f);


        FSlimeParticleController Ctl;
        Ctl.Center = Center;
        //Ctl.Center = FVector::ZeroVector;
        Ctl.Radius = Radius;
        Ctl.Velocity = bConnect ? ToMain : FVector::ZeroVector;
        Ctl.Concentration = Concentration;

        Controllers.Add(Ctl);

    }

    if (Controllers.Num() == 1)
    {
        bConnect = false;
    }
    //UE_LOG(LogTemp, Warning, TEXT("bConnect: %s"), bConnect ? TEXT("true") : TEXT("false"));
    RearrangeInstances();
}

void USlimePBFManager::RearrangeInstances()
{
    //实锟斤拷锟斤拷锟斤拷
    const int32 InstanceCount = SlimeInstances.Num();
    //UE_LOG(LogTemp, Warning, TEXT("InstanceCount锟斤拷%d"), InstanceCount);
    //UE_LOG(LogTemp, Warning, TEXT("ControllersCount锟斤拷%d"), Controllers.Num());
    if (InstanceCount - InstancePool.Num() > Controllers.Num())
    {
        //UE_LOG(LogTemp, Warning, TEXT("2222"));
        // 锟斤拷锟斤拷锟斤拷锟绞碉拷锟斤拷锟斤拷锟揭拷喜锟斤拷锟斤拷丫锟绞碉拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟?Controller锟斤拷
        TArray<bool> Used;
        Used.Init(false, InstanceCount);

        // 锟饺革拷每锟斤拷 controller 锟斤拷一锟斤拷锟斤拷锟皆硷拷锟斤拷锟斤拷摹锟斤拷锟矫伙拷霉锟斤拷锟?active slime
        for (int32 ControllerID = 0; ControllerID < Controllers.Num(); ++ControllerID)
        {
            const FVector Center = Controllers[ControllerID].Center;

            int32 BestInstance = -1;
            float BestDst2 = FLT_MAX;

            for (int32 j = 0; j < InstanceCount; ++j)
            {
                const FSlimeInstance& Slime = SlimeInstances[j];
                if (Used[j] || !Slime.bActive) continue;

                const float Dst2 = FVector::DistSquared(Center, Slime.Center);
                if (Dst2 < BestDst2)
                {
                    BestDst2 = Dst2;
                    BestInstance = j;
                }
            }

            if (BestInstance >= 0)
            {
                Used[BestInstance] = true;
                UpdateInstanceController(BestInstance, ControllerID);
            }
        }

        // 锟劫帮拷剩锟斤拷没锟矫碉拷锟斤拷 controller 锟斤拷锟斤拷锟铰碉拷 SlimeInstance
        for (int32 i = 0; i < InstanceCount; i++)
        {
            FSlimeInstance Slime = SlimeInstances[i];
            if (Used[i] || !Slime.bActive) continue;
            Slime.bActive = false;
            SlimeInstances[i] = Slime;
            InstancePool.Push(i);
        }
        Used.Reset();
        if (!SlimeInstances[ControlledInstance].bActive)
        {
            float BestDst = FLT_MAX;
            for (int i = 0; i < InstanceCount; i++)
            {
                FSlimeInstance Slime = SlimeInstances[i];
                if (!Slime.bActive) continue;

                float dst = FVector::DistSquared(MainControllerPosition , Slime.Center);
                if (dst < BestDst)
                {
                    BestDst = dst;
                    ControlledInstance = i;
                }
            }
            int controllerID = SlimeInstances[ControlledInstance].ControllerID;
            UpdateInstanceController(ControlledInstance, controllerID);
        }    
    }
    else
    {
        //UE_LOG(LogTemp, Warning, TEXT("1111"));
        TArray<bool> Used;
        Used.Init(false, Controllers.Num());
        for (int instanceID = 0; instanceID < SlimeInstances.Num(); instanceID++)
        {
            FSlimeInstance slime = SlimeInstances[instanceID];
            if (!slime.bActive)  continue;
            FVector pos = slime.Center;
            int controllerID = -1;
            float minDst = FLT_MAX;
            for (int j = 0; j < Controllers.Num(); j++)
            {
                if (Used[j]) continue;
                auto cl = Controllers[j];
                FVector center = cl.Center;
                float dst = FVector::DistSquared(center, pos);
                if (dst < minDst)
                {
                    minDst = dst;
                    controllerID = j;
                }
            }
            Used[controllerID] = true;
            UpdateInstanceController(instanceID, controllerID);
        }

        for (int i = 0; i < Controllers.Num(); i++)
        {
            if (Used[i]) continue;
            auto controller = Controllers[i];
            FVector dir = (
                controller.Velocity.SizeSquared() < 1e-3f ?
                (FVector)MainControllerPosition - controller.Center : controller.Velocity).GetSafeNormal(1e-4f, FVector::ForwardVector);

            FVector HitPos = FVector::ZeroVector;
            FVector HitNormal = FVector::UpVector;
            const bool bHitSurface = SampleSurfaceAttachment(controller.Center, dir, HitPos, HitNormal);
            if (!bHitSurface)
            {
                HitPos = controller.Center + dir * controller.Radius * 0.5f;
                HitNormal = (-dir).GetSafeNormal(1e-4f, FVector::UpVector);
            }

            FSlimeInstance NewSlime;
            NewSlime.bActive = true;
            NewSlime.Center = controller.Center;
            NewSlime.Radius = controller.Radius;
            NewSlime.Dir = dir;
            NewSlime.Pos = HitPos;
            NewSlime.SurfaceNormal = HitNormal;
            NewSlime.ControllerID = i;
            if (InstancePool.Num() > 0)
            {
                int32 ReuseIndex = InstancePool.Pop(false);
                SlimeInstances[ReuseIndex] = NewSlime;
            }
            else
            {
                SlimeInstances.Add(NewSlime);
            }
        }
        Used.Empty();
    }
}

float USlimePBFManager::SampleDensityTrilinear(const FVector& Pos) const
{
    if (GridLut.Num() == 0 || GridBuffer.Num() == 0)
    {
        return 0.0f;
    }

    auto ReadGridValue = [&](const FIntVector& Coord) -> float
        {
            const FIntVector Key = Coord >> 2;
            const int32* OffsetPtr = GridLut.Find(Key);
            if (!OffsetPtr)
            {
                return 0.0f;
            }

            const FIntVector LocalCoord = SlimePBFUtils::Mod4(Coord);
            const int32 LocalIdx = LocalCoord.X + 4 * (LocalCoord.Y + 4 * LocalCoord.Z);
            return GridBuffer[*OffsetPtr + LocalIdx];
        };

    const FVector Relative = (Pos - MinPos) / SlimePBFUtils::CellSize;
    const FIntVector P000(
        FMath::FloorToInt(Relative.X),
        FMath::FloorToInt(Relative.Y),
        FMath::FloorToInt(Relative.Z));
    const FIntVector P111 = P000 + FIntVector(1, 1, 1);
    const FVector Fraction = Relative - FVector(P000);

    const float C000 = ReadGridValue(P000);
    const float C100 = ReadGridValue(FIntVector(P111.X, P000.Y, P000.Z));
    const float C010 = ReadGridValue(FIntVector(P000.X, P111.Y, P000.Z));
    const float C110 = ReadGridValue(FIntVector(P111.X, P111.Y, P000.Z));
    const float C001 = ReadGridValue(FIntVector(P000.X, P000.Y, P111.Z));
    const float C101 = ReadGridValue(FIntVector(P111.X, P000.Y, P111.Z));
    const float C011 = ReadGridValue(FIntVector(P000.X, P111.Y, P111.Z));
    const float C111 = ReadGridValue(P111);

    const float C00 = FMath::Lerp(C000, C100, Fraction.X);
    const float C10 = FMath::Lerp(C010, C110, Fraction.X);
    const float C01 = FMath::Lerp(C001, C101, Fraction.X);
    const float C11 = FMath::Lerp(C011, C111, Fraction.X);
    const float C0 = FMath::Lerp(C00, C10, Fraction.Y);
    const float C1 = FMath::Lerp(C01, C11, Fraction.Y);
    return FMath::Lerp(C0, C1, Fraction.Z);
}

FVector USlimePBFManager::CalculateSurfaceNormal(const FVector& Pos) const
{
    const float Step = SlimePBFUtils::CellSize;
    const FVector OffsetX(Step, 0.0f, 0.0f);
    const FVector OffsetY(0.0f, Step, 0.0f);
    const FVector OffsetZ(0.0f, 0.0f, Step);

    const float Nx = SampleDensityTrilinear(Pos - OffsetX) - SampleDensityTrilinear(Pos + OffsetX);
    const float Ny = SampleDensityTrilinear(Pos - OffsetY) - SampleDensityTrilinear(Pos + OffsetY);
    const float Nz = SampleDensityTrilinear(Pos - OffsetZ) - SampleDensityTrilinear(Pos + OffsetZ);

    return FVector(Nx, Ny, Nz).GetSafeNormal(1e-4f, FVector::UpVector);
}

bool USlimePBFManager::SampleSurfaceAttachment(const FVector& StartPos, const FVector& Dir, FVector& OutHitPos, FVector& OutNormal) const
{
    const FVector TraceDir = Dir.GetSafeNormal(1e-4f, FVector::ForwardVector);
    const float StepSize = SlimePBFUtils::CellSize * 0.5f;
    const int32 MaxSteps = 24;

    FVector PrevPos = StartPos;
    float PrevValue = SampleDensityTrilinear(PrevPos);

    for (int32 StepIndex = 0; StepIndex < MaxSteps; ++StepIndex)
    {
        const FVector CurPos = PrevPos + TraceDir * StepSize;
        const float CurValue = SampleDensityTrilinear(CurPos);

        if (PrevValue >= Threshold && CurValue < Threshold)
        {
            FVector InsidePos = PrevPos;
            FVector OutsidePos = CurPos;

            for (int32 Iter = 0; Iter < 5; ++Iter)
            {
                const FVector MidPos = FMath::Lerp(InsidePos, OutsidePos, 0.5f);
                const float MidValue = SampleDensityTrilinear(MidPos);
                if (MidValue >= Threshold)
                {
                    InsidePos = MidPos;
                }
                else
                {
                    OutsidePos = MidPos;
                }
            }

            OutHitPos = FMath::Lerp(InsidePos, OutsidePos, 0.5f);
            OutNormal = CalculateSurfaceNormal(OutHitPos);
            if (OutNormal.IsNearlyZero())
            {
                OutNormal = (-TraceDir).GetSafeNormal(1e-4f, FVector::UpVector);
            }
            return true;
        }

        PrevPos = CurPos;
        PrevValue = CurValue;
    }

    OutHitPos = PrevPos;
    OutNormal = (-TraceDir).GetSafeNormal(1e-4f, FVector::UpVector);
    return false;
}

bool USlimePBFManager::RayHitSurface(const FVector& Pos, const FVector& Dir, FVector& OutHitPos) const
{
    FVector SurfaceNormal = FVector::UpVector;
    return SampleSurfaceAttachment(Pos, Dir, OutHitPos, SurfaceNormal);
}
void USlimePBFManager::UpdateInstanceController(int32 InstanceID, int32 ControllerID)
{
    FSlimeInstance& Slime = SlimeInstances[InstanceID];
    FSlimeParticleController& Ctl = Controllers[ControllerID];

    if (InstanceID == ControlledInstance)
    {
        Ctl.Velocity = MainControllerVelocity;
    }

    Slime.ControllerID = ControllerID;

    const float DT = SlimePBFUtils::DeltaTime;

    // Radius smoothly follows; Center snaps directly to avoid gap during bounce-back.
    Slime.Radius = FMath::Lerp(Slime.Radius, Ctl.Radius, 0.1f);
    Slime.Center = Ctl.Center;

    // --- Direction update: yaw-based rotation to guarantee horizontal sweep ---
    const FVector Vec = Ctl.Velocity;

    // Compute target yaw from velocity (or keep current yaw when idle)
    float TargetYaw = FMath::Atan2(Slime.Dir.Y, Slime.Dir.X);
    float TargetPitch = Slime.Dir.Z;
    bool bHasVelocity = Vec.SizeSquared() > 1e-4f;

    if (bHasVelocity)
    {
        FVector VelDir = Vec.GetSafeNormal(1e-4f, FVector::ForwardVector);
        TargetYaw = FMath::Atan2(VelDir.Y, VelDir.X);
        TargetPitch = FMath::Clamp(VelDir.Z, -0.2f, 0.5f);
    }
    else
    {
        TargetPitch = 0.0f; // settle to horizontal when idle
    }

    // Interpolate yaw via shortest angular path — never goes vertical
    const float CurrentYaw = FMath::Atan2(Slime.Dir.Y, Slime.Dir.X);
    const float DeltaYaw = FMath::FindDeltaAngleRadians(CurrentYaw, TargetYaw);
    const float AbsDeltaYaw = FMath::Abs(DeltaYaw);

    // Angular speed: smooth transition, no aggressive acceleration at large angles
    constexpr float BaseRotSpeed = 5.0f; // rad/s (~286 deg/s) — visible but not instant
    const float AngleFactor = 1.0f + 0.5f * (AbsDeltaYaw / PI); // mild 1.5x at 180°
    const float MaxYawStep = BaseRotSpeed * AngleFactor * DT;
    const float YawStep = FMath::Min(MaxYawStep, AbsDeltaYaw);
    const float NewYaw = CurrentYaw + FMath::Sign(DeltaYaw) * YawStep;

    // Pitch blends smoothly and independently
    const float CurrentPitch = Slime.Dir.Z;
    const float PitchAlpha = 1.0f - FMath::Exp(-10.0f * DT);
    const float NewPitch = FMath::Lerp(CurrentPitch, TargetPitch, PitchAlpha);

    // Reconstruct direction from yaw + pitch
    const float CosPitch = FMath::Sqrt(FMath::Max(1.0f - NewPitch * NewPitch, 0.0f));
    Slime.Dir = FVector(FMath::Cos(NewYaw) * CosPitch, FMath::Sin(NewYaw) * CosPitch, NewPitch);
    Slime.Dir = Slime.Dir.GetSafeNormal(1e-4f, FVector::ForwardVector);

    const float AngleRad = AbsDeltaYaw; // used later for TurnUrgency

    FVector TargetPos = FVector::ZeroVector;
    FVector TargetNormal = FVector::UpVector;
    if (SampleSurfaceAttachment(Ctl.Center, Slime.Dir, TargetPos, TargetNormal))
    {
        TargetNormal = TargetNormal.GetSafeNormal(1e-4f, FVector::UpVector);
    }
    else
    {
        TargetPos = Ctl.Center;
        TargetNormal = (-Slime.Dir).GetSafeNormal(1e-4f, FVector::UpVector);
    }

    // Eye anti-jitter: adaptive smoothing.
    // Position tracking scales with both motion speed and turn urgency.
    // Large displacement (bounce-back) triggers near-instant snap.
    const float MotionSpeed = Vec.Size();
    const float Motion01 = FMath::Clamp(MotionSpeed / 6.0f, 0.0f, 1.0f);
    const float TurnUrgency = FMath::Clamp(AngleRad / PI, 0.0f, 1.0f);

    const float BasePosSmoothHz = FMath::Lerp(8.0f, 20.0f, Motion01);
    const float PosSmoothHz = FMath::Lerp(BasePosSmoothHz, 40.0f, TurnUrgency);
    const float NormalSmoothHz = FMath::Lerp(6.0f, 20.0f, FMath::Max(Motion01, TurnUrgency));
    float PosAlpha = 1.0f - FMath::Exp(-PosSmoothHz * DT);
    const float NormalAlpha = 1.0f - FMath::Exp(-NormalSmoothHz * DT);

    // Distance-based snap: if eye is far from target (bounce-back), ramp alpha toward 1.
    const float PosDist = FVector::Dist(Slime.Pos, TargetPos);
    const float SnapThreshold = FMath::Max(0.1f, Slime.Radius * 0.15f);
    if (PosDist > SnapThreshold)
    {
        // Smoothly ramp to full snap as distance grows beyond threshold
        const float SnapBlend = FMath::Clamp((PosDist - SnapThreshold) / SnapThreshold, 0.0f, 1.0f);
        PosAlpha = FMath::Lerp(PosAlpha, 1.0f, SnapBlend);
    }

    // Dead zones suppress micro noise; shrink during turns and large displacement.
    const float DeadZoneScale = FMath::Lerp(1.0f, 0.1f, FMath::Max(TurnUrgency, FMath::Clamp(PosDist / SnapThreshold, 0.0f, 1.0f)));
    const float PosDeadZone = FMath::Max(0.02f, Slime.Radius * 0.015f) * DeadZoneScale;
    const float PosDeadZoneSq = PosDeadZone * PosDeadZone;
    if (FVector::DistSquared(Slime.Pos, TargetPos) < PosDeadZoneSq)
    {
        TargetPos = Slime.Pos;
    }

    const float NrmDot = FVector::DotProduct(
        Slime.SurfaceNormal.GetSafeNormal(1e-4f, FVector::UpVector),
        TargetNormal);
    if (NrmDot > FMath::Cos(FMath::DegreesToRadians(3.0f)))
    {
        TargetNormal = Slime.SurfaceNormal.GetSafeNormal(1e-4f, FVector::UpVector);
    }

    Slime.Pos = FMath::Lerp(Slime.Pos, TargetPos, PosAlpha);
    Slime.SurfaceNormal = FMath::Lerp(
        Slime.SurfaceNormal.GetSafeNormal(1e-4f, FVector::UpVector),
        TargetNormal,
        NormalAlpha).GetSafeNormal(1e-4f, FVector::UpVector);

    SlimeInstances[InstanceID] = Slime;

    if (InstanceID == ControlledInstance)
    {
        Ctl.Center = MainControllerPosition;
        Controllers[ControllerID] = Ctl;
    }
}
//Control End

//Bubble Start
void USlimePBFManager::UpdateBubblesEffect()
{
    BlockNum = GridLut.Num();
    if (BlockNum == 0) return;

    // ------------ 1. GenerateBubblesJobs (圆形发射区域) -------------
    {
        FRandomStream Rnd(FMath::Rand());

        // 获取当前控制的史莱姆实例，用于确定发射位置
        FVector SlimeCenter = FVector::ZeroVector;
        FVector SlimeDir = FVector::ForwardVector;
        bool bHasActiveSlime = false;

        if (SlimeInstances.IsValidIndex(ControlledInstance) && SlimeInstances[ControlledInstance].bActive)
        {
            const FSlimeInstance& Slime = SlimeInstances[ControlledInstance];
            SlimeCenter = Slime.Center;
            SlimeDir = Slime.Dir;
            bHasActiveSlime = true;
        }
        else
        {
            // 回退：使用密度场中心
            SlimeCenter = (MinPos + MaxPos) * 0.5f;
            bHasActiveSlime = true;
        }

        if (bHasActiveSlime)
        {
            // 计算左右方向（垂直于朝向方向的水平分量）
            FVector FlatDir = FVector(SlimeDir.X, SlimeDir.Y, 0.0f);
            if (FlatDir.SizeSquared() < 1e-6f) FlatDir = FVector::ForwardVector;
            FlatDir.Normalize();

            // 右方向 = 朝向 × 上方向
            const FVector RightDir = FVector::CrossProduct(FlatDir, FVector::UpVector).GetSafeNormal();

            // 两个发射区域的中心：左下和右下
            const FVector DownOffset = FVector(0, 0, -BubbleEmitDownOffset);
            const FVector LeftEmitCenter  = SlimeCenter + (-RightDir) * BubbleEmitSideOffset + DownOffset;
            const FVector RightEmitCenter = SlimeCenter + RightDir * BubbleEmitSideOffset + DownOffset;

            // 对两个发射区域分别生成泡泡
            const FVector EmitCenters[2] = { LeftEmitCenter, RightEmitCenter };

            for (int32 Zone = 0; Zone < 2; ++Zone)
            {
                const FVector& EmitCenter = EmitCenters[Zone];
                int32 SpawnCount = 0;

                for (int32 Attempt = 0; Attempt < BubbleEmitMaxPerZone * 10; ++Attempt)
                {
                    if (SpawnCount >= BubbleEmitMaxPerZone) break;
                    if (BubblesPoolStack.Num() < 1) return;

                    // 概率控制
                    if (Rnd.GetFraction() > 0.05f * BubbleSpeed) continue;

                    // 在圆形区域内随机采样（均匀分布）
                    const float Angle = Rnd.GetFraction() * 2.0f * PI;
                    const float Dist = FMath::Sqrt(Rnd.GetFraction()) * BubbleEmitRadius;
                    const float OffX = FMath::Cos(Angle) * Dist;
                    const float OffY = FMath::Sin(Angle) * Dist;

                    // 将圆形采样映射到世界平面（XY平面）
                    FVector SpawnPos = EmitCenter + FVector(OffX, OffY, Rnd.GetFraction() * 0.5f);

                    // 检查生成点是否在密度场内（确保泡泡从史莱姆体内开始）
                    const float Density = SampleDensityTrilinear(SpawnPos);
                    if (Density < Threshold * 0.5f) continue;

                    const int32 Id = BubblesPoolStack[0];
                    BubblesPoolStack.RemoveAtSwap(0);

                    const float Radius = (Rnd.GetFraction() * 0.7f + 0.3f) * SlimePBFUtils::CellSize;
                    FSlimeBubble Bubble;
                    Bubble.Pos = SpawnPos;
                    Bubble.Radius = Radius;
                    Bubble.Vel = FVector(OffX * 0.3f, OffY * 0.3f, Radius * 2.0f); // 从圆心向外+向上
                    Bubble.LifeTime = 1.0f;

                    BubblesBuffer[Id] = Bubble;
                    SpawnCount++;
                }
            }
        }
    }

    // ------------ 2. BubblesViscosityJob  -------------
    const int32 BubbleCount = BubblesBuffer.Num();
    ParallelFor(BubbleCount, [&](int32 i)
        {
            FSlimeBubble Bubble = BubblesBuffer[i];
            if (Bubble.LifeTime < 0.0f) return;

            FVector Vel = Bubble.Vel;
            const FVector Pos = Bubble.Pos;

            const FIntVector Coord = SlimePBFUtils::GetCoord(Pos);
            FVector ViscosityVel = FVector::ZeroVector;
            float   Rho = 0.0f;

            for (int32 dz = -1; dz <= 1; ++dz)
                for (int32 dy = -1; dy <= 1; ++dy)
                    for (int32 dx = -1; dx <= 1; ++dx)
                    {
                        const FIntVector NeighborCoord = Coord + FIntVector(dx, dy, dz);
                        const int32 Key = SlimePBFUtils::GetKey(NeighborCoord);

                        FIntVector2* RangePtr = Lut.Find(Key);
                        if (!RangePtr) continue;
                        const FIntVector2 Range = *RangePtr;

                        for (int32 j = Range.X; j < Range.Y; ++j)
                        {
                            const FVector Dir = Pos - Particles[j].Position;
                            const float   R2 = Dir.SizeSquared();
                            if (R2 > SlimePBFUtils::h2) continue;

                            const float Weight = SlimePBFUtils::SmoothingKernelPoly6(R2);
                            ViscosityVel += VelocityBuffer[j] * Weight;
                            Rho += Weight;
                        }
                    }

            if (Rho > 1e-5f)
            {
                ViscosityVel /= Rho;
            }
            else
            {
                ViscosityVel = FVector::ZeroVector;
            }

            // 只对 Z 轴施加轻微粘性阻尼，XY 保持泡泡自身速度不被拉向中心
            const float SafeViscosity = FMath::Clamp(ViscosityStrength / 50.0f, 0.0f, 1.0f);
            const float XYDamping = 0.00f; // 极小的 XY 粘性，避免汇聚

            FVector NewVel;
            NewVel.X = FMath::Lerp(Vel.X, ViscosityVel.X, XYDamping);
            NewVel.Y = FMath::Lerp(Vel.Y, ViscosityVel.Y, XYDamping);
            NewVel.Z = FMath::Lerp(Vel.Z, ViscosityVel.Z, SafeViscosity);

            Bubble.Vel = NewVel;
            BubblesBuffer[i] = Bubble;
        });

    // ------------ 3. UpdateBubblesJob -------------
    {
        auto GetLocalIndex = [](const FIntVector& C)->int32 {
            return C.X + 4 * (C.Y + 4 * C.Z);
            };

        for (int32 i = 0; i < BubbleCount; ++i)
        {
            FSlimeBubble& B = BubblesBuffer[i];
            if (B.LifeTime < 0.0f) continue;

            B.Vel.Z += B.Radius * B.Radius * SlimePBFUtils::DeltaTime * 10.0f;
            // 限制最大上升速度，防止泡泡在表面附近反复弹跳
            B.Vel.Z = FMath::Min(B.Vel.Z, 3.0f);
            B.Pos += B.Vel * SlimePBFUtils::DeltaTime * 2.0f;
            B.LifeTime += SlimePBFUtils::DeltaTime;
            const float Scale = 1.002f;
            B.Radius *= Scale;

            const FVector Relative = (B.Pos - MinPos) / SlimePBFUtils::CellSize;
            const FIntVector Coord(
                FMath::FloorToInt(Relative.X),
                FMath::FloorToInt(Relative.Y),
                FMath::FloorToInt(Relative.Z));

            const FIntVector Key = Coord >> 2;
            const int32* OffsetPtr = GridLut.Find(Key);
            bool bDead = false;

            if (!OffsetPtr)
            {
                bDead = true;
            }
            else
            {
                const int32 Offset = *OffsetPtr;
                const int32 LocalIdx = GetLocalIndex(SlimePBFUtils::Mod4(Coord));
                const float Data = GridBuffer[Offset + LocalIdx];
                // 用更宽松的阈值：泡泡刚到达表面附近就判定离开
                if (Data < Threshold * 0.8f)
                {
                    bDead = true;
                }
            }

            if (bDead)
            {
                // 触发泡泡破裂特效（只要存活超过最小时间即可）
                if (B.LifeTime > 0.15f && OnBubblePopped.IsBound())
                {
                    // 将模拟空间的坐标和半径转换回 UE 的世界坐标系
                    FVector WorldPos = B.Pos * SlimePBFUtils::InvScale;
                    float WorldRadius = B.Radius * SlimePBFUtils::InvScale;
                    OnBubblePopped.Broadcast(WorldPos, WorldRadius);
                }
                B.LifeTime = -1.0f;
                B.Radius = 0.0f;
                BubblesPoolStack.Add(i);
            }
        }
    }

    BubblesNum = SlimePBFUtils::BubblesCount - BubblesPoolStack.Num();
}
//Bubble End
void USlimePBFManager::DebugDraw(UWorld* World)
{
    if (!World) return;

    const float DrawScale = SlimePBFUtils::InvScale;

    // 锟斤拷锟斤拷锟斤拷锟斤拷
    //for (int32 i = 0; i < Particles.Num(); i += 20) {
    //    // 使锟斤拷 ParticlesTemp锟斤拷锟斤拷为锟斤拷锟斤拷锟斤拷锟斤拷染锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
    //    FVector WorldPos = ParticlesTemp[i].Position * WorldScale;
    //    DrawDebugPoint(World, WorldPos, 4.0f, FColor::Red, false, -1.0f);
    //}

    // 锟斤拷锟斤拷实锟斤拷锟斤拷锟斤拷
    /*for (int32 i = 0; i < SlimeInstances.Num(); i++)
    {
        const FSlimeInstance& S = SlimeInstances[i];
        if (!S.bActive) continue;

        FVector WorldCenter = S.Center * WorldScale;
        float WorldRadius = S.Radius * WorldScale;

        DrawDebugSphere(World, WorldCenter, WorldRadius, 16, FColor::Cyan, false, -1.0f, 0, 1.0f);
    }*/
    // 锟斤拷锟斤拷锟斤拷撞锟斤拷
    //for (const FMyBoxCollider& box : _colliderBuffer)
    //{
    //    // 锟斤拷锟斤拷锟?Transform.Location 锟斤拷锟斤拷锟斤拷锟斤拷 Init 时锟斤拷锟斤拷 1.5 锟斤拷
    //    // 锟斤拷锟斤拷锟斤拷锟斤拷嘶锟?DrawScale (10 * 1.5)锟斤拷锟斤拷锟矫伙拷原锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
    //    FVector Center = box.Transform.GetLocation() * DrawScale;
    //    FVector Extent = box.Extent * DrawScale;

    //    FQuat Rotation = box.Transform.GetRotation();
    //    DrawDebugBox(World, Center, Extent, Rotation, FColor::Green, false, -1.0f, 0, 3.0f);
    //}
}



