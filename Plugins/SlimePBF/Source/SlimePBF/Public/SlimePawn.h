#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SlimePBFInstancedMeshComponent.h" 
#include "SlimePawn.generated.h"

class USphereComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SLIMEPBF_API ASlimePawn : public APawn
{
    GENERATED_BODY()

public:
    ASlimePawn();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // --- 组件 ---
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slime")
    USphereComponent* SphereComponent; // 物理核心

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slime")
    USlimePBFInstancedMeshComponent* SlimePBFComponent; // 挂载 PBF 管理器

    // --- 移动参数
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slime Control")
    float MoveSpeed = 20.0f; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slime Control")
    float JumpForce = 120.0f; 

    // 专门用于渲染史莱姆眼睛的实例组件
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slime")
    class UInstancedStaticMeshComponent* EyeInstancedMeshComp;

    // --------- 新增：专门用于渲染泡泡的实例组件 ---------
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slime")
    class UInstancedStaticMeshComponent* BubbleInstancedMeshComp;

    // 输入处理函数
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Jump();
private:
    FVector CurrentInput; // 存储当前的 WASD 输入
};