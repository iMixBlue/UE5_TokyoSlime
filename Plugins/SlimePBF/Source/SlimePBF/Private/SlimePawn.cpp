#include "SlimePawn.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

ASlimePawn::ASlimePawn()
{
    PrimaryActorTick.bCanEverTick = true;

    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    SphereComponent->InitSphereRadius(32.0f); 
    SphereComponent->SetSimulatePhysics(true); 
    SphereComponent->SetCollisionProfileName(TEXT("PhysicsActor"));

    RootComponent = SphereComponent;

    SlimePBFComponent = CreateDefaultSubobject<USlimePBFInstancedMeshComponent>(TEXT("SlimePBFComp"));
    SphereComponent->SetHiddenInGame(true);
    CurrentInput = FVector::ZeroVector;

    EyeInstancedMeshComp = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("EyeInstancedMeshComp"));
    EyeInstancedMeshComp->SetupAttachment(RootComponent);
    EyeInstancedMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 眼睛不需要物理碰撞
    EyeInstancedMeshComp->SetCastShadow(false);

    EyeInstancedMeshComp->SetUsingAbsoluteLocation(true);
    EyeInstancedMeshComp->SetUsingAbsoluteRotation(true);
    EyeInstancedMeshComp->SetUsingAbsoluteScale(true);

    // --------- 新增：初始化泡泡渲染组件 ---------
    BubbleInstancedMeshComp = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("BubbleInstancedMeshComp"));
    BubbleInstancedMeshComp->SetupAttachment(RootComponent);
    BubbleInstancedMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 泡泡不需要物理碰撞
    BubbleInstancedMeshComp->SetCastShadow(false); // 泡泡如果是半透明材质通常不投射阴影
    BubbleInstancedMeshComp->SetUsingAbsoluteLocation(true);
    BubbleInstancedMeshComp->SetUsingAbsoluteRotation(true);
    BubbleInstancedMeshComp->SetUsingAbsoluteScale(true);
}

void ASlimePawn::BeginPlay()
{
    Super::BeginPlay();
}

void ASlimePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 1. 获取输入并计算期望速度 (类似 Unity: speed * input.normalized)
    FVector DesiredVelocity = CurrentInput.GetSafeNormal() * MoveSpeed;
    FVector CurrentPhysVelocity = SphereComponent->GetPhysicsLinearVelocity();

    // 2. 直接覆盖水平速度，保留垂直速度 (类似 Unity: velocity.y = current.y)
    FVector FinalVelocity = DesiredVelocity;
    FinalVelocity.Z = CurrentPhysVelocity.Z;

    // 3. 应用速度到刚体
    SphereComponent->SetPhysicsLinearVelocity(FinalVelocity);

    // 4. 同步给 PBF Manager
    if (SlimePBFComponent && SlimePBFComponent->PBFManager)
    {
        SlimePBFComponent->PBFManager->UpdateMainControllerPosition(GetActorLocation());
        SlimePBFComponent->PBFManager->UpdateMainControllerVelocity(FinalVelocity);
    }

    // 重置输入
    CurrentInput = FVector::ZeroVector;
}

void ASlimePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ASlimePawn::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASlimePawn::MoveRight);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASlimePawn::Jump);
}

void ASlimePawn::MoveForward(float Value)
{
    CurrentInput.X = Value;
}

void ASlimePawn::MoveRight(float Value)
{
    CurrentInput.Y = Value;
}

void ASlimePawn::Jump()
{
    FVector Vel = SphereComponent->GetPhysicsLinearVelocity();
    Vel.Z = JumpForce;

    SphereComponent->SetPhysicsLinearVelocity(Vel);
}