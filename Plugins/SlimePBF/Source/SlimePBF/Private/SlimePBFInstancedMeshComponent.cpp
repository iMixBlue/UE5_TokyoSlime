#include "SlimePBFInstancedMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

USlimePBFInstancedMeshComponent::USlimePBFInstancedMeshComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    PBFManager = CreateDefaultSubobject<USlimePBFManager>(TEXT("PBFManager"));
}

void USlimePBFInstancedMeshComponent::BeginPlay()
{
    Super::BeginPlay();

    AActor* Owner = GetOwner();
    if (!Owner) return;
    if (Owner) {
        AddTickPrerequisiteActor(Owner); // 强制让 Mesh 在 Pawn 动完之后再算
        PrimaryComponentTick.TickGroup = TG_PostPhysics;
    }

    TArray<UInstancedStaticMeshComponent*> ISMComps;
    Owner->GetComponents<UInstancedStaticMeshComponent>(ISMComps);
    for (auto* ISM : ISMComps)
    {
        FString CompName = ISM->GetName();
        
        // 精准分配！
        if (CompName.Contains(TEXT("EyeInstancedMeshComp")))
        {
            EyeInstancedMeshComponent = ISM;
        }
        else if (CompName.Contains(TEXT("BubbleInstancedMeshComp")))
        {
            BubbleInstancedMeshComponent = ISM;
        }
        else 
        {
            // 如果既不是 Eye 也不是 Bubble，那它就是渲染粒子的 ISM
            InstancedMeshComponent = ISM;
        }
    }

    if (bAutoInitialize && PBFManager)
    {
        if (!PBFManager->SurfaceMesh) PBFManager->SurfaceMesh = Owner->FindComponentByClass<UProceduralMeshComponent>();

        //设为绝对坐标
        PBFManager->SurfaceMesh->SetUsingAbsoluteLocation(true);
        PBFManager->SurfaceMesh->SetUsingAbsoluteRotation(true);
        PBFManager->SurfaceMesh->SetUsingAbsoluteScale(true);

        if (ParticleMaterial && PBFManager->SurfaceMesh->GetNumMaterials() == 0)
        {
            PBFManager->SurfaceMesh->SetMaterial(0, ParticleMaterial);
        }
        InitializePBF();
    }
}

void USlimePBFInstancedMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (PBFManager && bIsInitialized)
    {
        AccumulatedTime += DeltaTime;

        // Unity Like FixedUpdate
        while (AccumulatedTime >= FixedDeltaTime) 
        {
        for (int i = 0; i < 2; i++)
        {
            PBFManager->UpdateSimulation();
         }
            PBFManager->UpdateSurface();
            PBFManager->UpdateControl();
            PBFManager->DebugDraw(GetWorld());
            PBFManager->UpdateBubblesEffect();
            AccumulatedTime -= FixedDeltaTime;
        }  
        UpdateEyeInstances();
        UpdateBubbleInstances();
    }
}

void USlimePBFInstancedMeshComponent::UpdateEyeInstances()
{
    if (!EyeInstancedMeshComponent || !PBFManager) return;

    const TArray<USlimePBFManager::FSlimeInstance>& Instances = PBFManager->SlimeInstances;

    // 统计当前处于激活状态的史莱姆数量
    int32 ActiveCount = 0;
    for (const auto& Slime : Instances)
    {
        if (Slime.bActive) ActiveCount++;
    }

    if (PBFManager->Concentration <= 5.0f || ActiveCount == 0)
    {
        if (EyeInstancedMeshComponent->GetInstanceCount() > 0)
        {
            EyeInstancedMeshComponent->ClearInstances();
        }
        return;
    }

    int32 CurrentInstanceCount = EyeInstancedMeshComponent->GetInstanceCount();

    // 动态调整 Instance 数量池，避免每帧 Clear 然后 Add，提升性能
    if (CurrentInstanceCount > ActiveCount)
    {
        for (int i = CurrentInstanceCount - 1; i >= ActiveCount; --i)
        {
            EyeInstancedMeshComponent->RemoveInstance(i);
        }
    }
    else if (CurrentInstanceCount < ActiveCount)
    {
        for (int i = CurrentInstanceCount; i < ActiveCount; ++i)
        {
            EyeInstancedMeshComponent->AddInstance(FTransform::Identity);
        }
    }

    // 遍历写入最新的 Transform 数据
    int32 InstanceIndex = 0;
    for (int32 i = 0; i < Instances.Num(); ++i)
    {
        const auto& Slime = Instances[i];
        if (!Slime.bActive) continue;

        // 1. 位置映射：Slime.Pos 目前是模拟空间，乘以 InvScale 转为世界空间渲染坐标
        FVector WorldPos = Slime.Pos * SlimePBFUtils::InvScale;
        WorldPos.Z += EyeHeightOffset;

        // 2. 旋转映射
        FRotator WorldRot = (Slime.Dir).Rotation();

        // 3. 缩放映射
        float RawScale = FMath::Sqrt(Slime.Radius * SlimePBFUtils::Scale);
        FVector WorldScale = FVector(RawScale * EyeScaleMultiplier);

        FTransform NewTransform(WorldRot, WorldPos, WorldScale);

        EyeInstancedMeshComponent->UpdateInstanceTransform(InstanceIndex, NewTransform, true, true, false);
        InstanceIndex++;
    }
}

void USlimePBFInstancedMeshComponent::UpdateBubbleInstances()
{
    if (!BubbleInstancedMeshComponent || !PBFManager) return;

    const TArray<USlimePBFManager::FSlimeBubble>& Bubbles = PBFManager->BubblesBuffer;

    // 统计目前存活的泡泡
    int32 ActiveCount = 0;
    for (const auto& B : Bubbles)
    {
        if (B.LifeTime > 0.0f) ActiveCount++;
    }

    int32 CurrentInstanceCount = BubbleInstancedMeshComponent->GetInstanceCount();

    // 动态调整 Instance 数量，避免每帧 Clear
    if (CurrentInstanceCount > ActiveCount)
    {
        for (int i = CurrentInstanceCount - 1; i >= ActiveCount; --i)
        {
            BubbleInstancedMeshComponent->RemoveInstance(i);
        }
    }
    else if (CurrentInstanceCount < ActiveCount)
    {
        for (int i = CurrentInstanceCount; i < ActiveCount; ++i)
        {
            BubbleInstancedMeshComponent->AddInstance(FTransform::Identity);
        }
    }

    // 写入渲染坐标
    int32 InstanceIndex = 0;
    for (int32 i = 0; i < Bubbles.Num(); ++i)
    {
        const auto& B = Bubbles[i];
        if (B.LifeTime < 0.0f) continue; // 跳过死亡泡泡

        // 1. 位置映射：从模拟空间转为世界空间
        FVector WorldPos = B.Pos * SlimePBFUtils::InvScale;

        // 2. 缩放映射 (球体网格默认直径可能是100，你需要根据你的 BubbleMesh 自行决定这里的缩放倍率)
        float WorldScale = (B.Radius * 2.0f * SlimePBFUtils::InvScale) / 100.0f * BubbleScaleMultiplier;
        
        FTransform NewTransform(FRotator::ZeroRotator, WorldPos, FVector(WorldScale));
        BubbleInstancedMeshComponent->UpdateInstanceTransform(InstanceIndex, NewTransform, true, true, false);
        InstanceIndex++;
    }
}

void USlimePBFInstancedMeshComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (InstancedMeshComponent)
    {
        InstancedMeshComponent->ClearInstances();
    }
    Super::EndPlay(EndPlayReason);
}

void USlimePBFInstancedMeshComponent::InitializePBF()
{
    if (PBFManager)
    {
         PBFManager->InitializeSimulation(GetWorld());
         bIsInitialized = true;
    }
}


