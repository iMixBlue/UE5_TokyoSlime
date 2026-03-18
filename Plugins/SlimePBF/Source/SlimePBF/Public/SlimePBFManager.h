#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SlimePBFTypes.h"
#include "ProceduralMeshComponent.h"
#include "SlimePBFManager.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlimeBubblePopped, FVector, PopWorldPosition, float, BubbleWorldRadius);


UCLASS(Blueprintable)
class SLIMEPBF_API USlimePBFManager : public UObject
{
    GENERATED_BODY()

public:
    USlimePBFManager();
    virtual ~USlimePBFManager() override;

    UFUNCTION(BlueprintCallable, Category = "SlimePBF")
    void InitializeSimulation(UWorld* InWorld);

    UFUNCTION(BlueprintCallable, Category = "SlimePBF")
    void UpdateSimulation();

    TArray<FSlimeParticle>& GetRowParticles() { return Particles; }
    TArray<FSlimeParticle>& GetNewParticles() { return ParticlesTemp; }

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slime|Control")
    FVector MainControllerPosition = FVector::ZeroVector;   // 世界坐标

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slime|Control")
    FVector MainControllerVelocity = FVector::ZeroVector;   // 世界空间速度

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slime|Control")
    float Concentration = 30.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slime|Simulation")
    float Gravity = -5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slime|Simulation")
    float ViscosityStrength = 3.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slime|Surface")
    float Threshold = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slime|Surface")
    bool bUseAnisotropic = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slime|Effects")
    float BubbleSpeed = 0.2f;

    /** 泡泡发射圆的半径（模拟空间） */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slime|Effects")
    float BubbleEmitRadius = 1.5f;

    /** 发射圆心相对史莱姆中心的左右偏移距离（模拟空间） */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slime|Effects")
    float BubbleEmitSideOffset = 2.0f;

    /** 发射圆心相对史莱姆中心的向下偏移（模拟空间，正值=向下） */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slime|Effects")
    float BubbleEmitDownOffset = 1.0f;

    /** 每帧每个发射区域的最大生成数量 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slime|Effects")
    int32 BubbleEmitMaxPerZone = 3;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slime|Control")
    TArray<FSlimeParticleController> Controllers;

    UPROPERTY(BlueprintAssignable, Category = "Slime|Effects")
    FOnSlimeBubblePopped OnBubblePopped;

    // 调试用
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slime|Surface")
    FVector MinPos = FVector::ZeroVector;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slime|Surface")
    FVector MaxPos = FVector::ZeroVector;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slime|Surface")
    int32 BlockNum = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slime|Effects")
    int32 BubblesNum = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slime|Debug")
    bool bDebugMode = false; 

    UFUNCTION(BlueprintCallable, Category = "Slime|Control")
    void OnKeyP();

    UFUNCTION(BlueprintCallable, Category = "Slime|Control")
    void OnKeyR();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UProceduralMeshComponent* SurfaceMesh = nullptr;

    struct FMyBoxCollider
    {
        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FVector Center;

        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FVector Extent;
        FTransform Transform;
        FTransform InverseTransform;
    };

    struct FSlimeComponent
    {
        int32   ID = 0;
        FVector Center = FVector::ZeroVector;          
        FVector BoundsMin = FVector(FLT_MAX, FLT_MAX, FLT_MAX);
        FVector BoundsMax = FVector(-FLT_MAX, -FLT_MAX, -FLT_MAX);
        int32   CellCount = 0;
    };

    struct FSlimeBubble
    {
        FVector Pos = FVector::ZeroVector;   
        float   Radius = 0.0f;
        FVector Vel = FVector::ZeroVector;
        float   LifeTime = -1.0f;           // <0 = 死亡
    };

    
    struct FSlimeInstance
    {
        bool    bActive = false;
        FVector Center = FVector::ZeroVector; // controller Center  
        FVector Pos = FVector::ZeroVector;    // 面部位置
        FVector Dir = FVector::ForwardVector;
        FVector SurfaceNormal = FVector::UpVector;
        float   Radius = 1.0f;
        int32   ControllerID = -1;
    };

    // 组件 & Grid
    TArray<FVector> BoundsBuffer;         // size = 2，min / max
    TArray<float>  GridBuffer;            // size = GridSize * GridNum
    TArray<float>  GridTempBuffer;        // Blur 用
    TArray<int32>  GridIDBuffer;          // 每个 grid cell 属于哪个 component
    TMap<FIntVector, int32> GridLut;      // block key -> offset

    // 组件 & 实例
    TArray<FSlimeComponent> ComponentsBuffer;
    TArray<FSlimeInstance>  SlimeInstances;
    TArray<int32>           InstancePool;
    int32                   ControlledInstance = 0;
    bool                    bConnect = false;

    // 泡泡
    TArray<FSlimeBubble>    BubblesBuffer;
    TArray<int32>           BubblesPoolStack;

    void UpdateSurface();                                    // 密度场
    void UpdateControl();                                    // 控制多只史莱姆
    void UpdateBubblesEffect();                              // 泡泡
    void UpdateInstanceController(int32 InstanceID, int32 ControllerID);

    // 工具函数
    bool RayHitSurface(const FVector& StartPos, const FVector& Dir, FVector& OutHitPos) const;
    bool SampleSurfaceAttachment(const FVector& StartPos, const FVector& Dir, FVector& OutHitPos, FVector& OutNormal) const;
    void UpdateMainControllerVelocity(FVector newVelocity);
    void UpdateMainControllerPosition(FVector newPos);
    void DebugDraw(UWorld* World);
private:
    // Simulation Functions
    void ApplyForces();
    void BuildHash();
    void BuildLut(); 
    void BuildShuffle();
    void ComputeLambda();
    void ComputeDeltaPos();
    void UpdateParticles();
    void ApplyViscosity();
    void RearrangeInstances();
    


    //Surface Functions
    //render
    void ComputeMeanPos();
    void ComputeCovariance();
    void CalcBounds();

    //Allocate
    void ClearGrid();
    void AllocateBlock();
    void ColorBlock(); //如果不写color8，就不需要了
    
    //Splat光栅化
    void DensityProjectionParallel();

    //Blur
    void GridBlur();

    //Marching cubes
    void MarchingCubesParallel();

    //CCA连通域分割
    void ConnectComponentBlock();
    void ParticleIDParallel();
    float SampleDensityTrilinear(const FVector& Pos) const;
    FVector CalculateSurfaceNormal(const FVector& Pos) const;



    // 粒子数据
    TArray<FSlimeParticle> Particles;
    TArray<FSlimeParticle> ParticlesTemp;
    TArray<FVector> PosPredict;
    TArray<FVector> PosOld;
    TArray<float> LambdaBuffer;
    TArray<FVector> VelocityBuffer;
    TArray<FVector> VelocityTempBuffer;
    TArray<FMyBoxCollider> _colliderBuffer;

    // 空间哈希
    TMap<int32, FIntVector2> Lut;
    TArray<FIntVector2> Hashes;
    TArray<FMatrix> GMatrixBuffer;

    TArray<FIntVector>VertPos;
    TArray<int32> _triangleConnectionTable;
    TArray<int32> _triangleVertCountTable;
    TArray<int32> _cubeEdgeFlags;
    TArray<FIntVector2> EdgeVert;


    // 内部状态
    bool bInitialized = false;
    bool bReadyForControl = false;
    FVector ExternalForce = FVector::ZeroVector;
};

