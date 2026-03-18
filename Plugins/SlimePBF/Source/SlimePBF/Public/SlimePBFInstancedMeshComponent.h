#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "SlimePBFManager.h"
#include "SlimePBFInstancedMeshComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SLIMEPBF_API USlimePBFInstancedMeshComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USlimePBFInstancedMeshComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SlimePBF")
    UInstancedStaticMeshComponent* InstancedMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlimePBF")
    USlimePBFManager* PBFManager;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlimePBF")
    bool bAutoInitialize = true;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SlimePBF")
    bool bIsInitialized = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlimePBF|Visual")
    UStaticMesh* ParticleMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlimePBF|Visual")
    UMaterialInterface* ParticleMaterial;

    UFUNCTION(BlueprintCallable, Category = "SlimePBF")
    void InitializePBF();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SlimePBF")
    UInstancedStaticMeshComponent* EyeInstancedMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlimePBF|Visual")
    float EyeScaleMultiplier = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlimePBF|Visual")
    float EyeSurfaceOffset = 0.2f;

    /** 眼睛在Z轴方向的额外高度偏移（世界空间单位） */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlimePBF|Visual")
    float EyeHeightOffset = 5.0f;  // 用于在蓝图里自由放大或缩小泡泡

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlimePBF|Visual")
    float BubbleScaleMultiplier = 1.0f;

    // --------- 新增：泡泡组件引用 ---------
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SlimePBF")
    UInstancedStaticMeshComponent* BubbleInstancedMeshComponent;

private:
    float AccumulatedTime = 0.0f;
    static constexpr float FixedDeltaTime = 0.02f;
    void UpdateEyeInstances();
    void UpdateBubbleInstances();
};
