// Fill out your copyright notice in the Description page of Project Settings.


#include "GunCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Team1MiniGame/Weapon/Projectile.h"
#include "Team1MiniGame/MyPlayerController.h"
#include "Team1MiniGame/MyHUD.h"

// Sets default values
AGunCharacter::AGunCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    CameraBoom->SetupAttachment(GetRootComponent());
    CameraBoom->TargetArmLength = 600.0f;
    CameraBoom->bUsePawnControlRotation = true;

    ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
    ViewCamera->SetupAttachment(CameraBoom);

    bMoveEnable = false;
    bIsCanFire = true;

    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
    WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("hand_rSocket"));
}

// Called when the game starts or when spawned
void AGunCharacter::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AGunCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FHitResult HitResult;
    TraceUnderCrosshairs(HitResult);

    SetHUDCrosshairs(DeltaTime);
}

void AGunCharacter::MoveForward(float Value)
{
    if (!bMoveEnable) return;

    if (Controller != nullptr && (Value != 0.f))
    {
        // ビューカメラのヨー軸の回転を変数に保存
        const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);

        // ヨー軸の変換マトリックスからX軸の方向ベクトルを取得
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        // ビューカメラのX軸を基づいてに移動
        AddMovementInput(Direction, Value);
    }
}

void AGunCharacter::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void AGunCharacter::Lookup(float Value)
{
    AddControllerPitchInput(Value);
}

void AGunCharacter::MoveRight(float Value)
{
    if (!bMoveEnable) return;

    if (Controller != nullptr && (Value != 0.f))
    {
        // ビューカメラのヨー軸の回転を変数に保存
        const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);

        // ヨー軸の変換マトリックスからY軸の方向ベクトルを取得
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // ビューカメラのY軸を基づいてに移動
        AddMovementInput(Direction, Value);
    }
}

void AGunCharacter::EquipKeyPressed()
{
}

void AGunCharacter::FireButtonPressed()
{
    if (bIsCanFire)
    {
        bIsFiring = true;
        bIsCanFire = false;
    }
}

void AGunCharacter::TraceUnderCrosshairs(FHitResult& TraceHitResult)
{
    FVector2D ViewportSize;
    if (GEngine && GEngine->GameViewport)
    {
        GEngine->GameViewport->GetViewportSize(ViewportSize);
    }

    FVector2D CrosshairLocation(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);
    FVector CrosshairWorldPosition;
    FVector CrosshairWorldDirection;

    bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
        UGameplayStatics::GetPlayerController(this, 0),
        CrosshairLocation,
        CrosshairWorldPosition,
        CrosshairWorldDirection);

    if (bScreenToWorld)
    {
        FVector Start = CrosshairWorldPosition;
        FVector End = Start + CrosshairWorldDirection * TRACE_LENGTH;

        GetWorld()->LineTraceSingleByChannel(
            TraceHitResult,
            Start,
            End,
            ECC_Visibility);

        if (!TraceHitResult.bBlockingHit)
        {
            TraceHitResult.ImpactPoint = End;
            Hit_Target = End;
        }
        else
        {
            Hit_Target = TraceHitResult.ImpactPoint;
        }

    }

}

void AGunCharacter::FireFromVector(const FVector& HitTarget)
{
    const auto MuzzleSocket = GetMesh()->GetSocketByName(FName("Muzzle"));

    if (MuzzleSocket)
    {
        FTransform SocketTransform = MuzzleSocket->GetSocketTransform(GetMesh());

        FVector ToTarget = HitTarget - SocketTransform.GetLocation();
        FRotator TargetRotation = ToTarget.Rotation();

        if (ProjectileClass)
        {
            FActorSpawnParameters SpawnParameters;
            SpawnParameters.Owner = this;
            SpawnParameters.Instigator = this;

            UWorld* World = GetWorld();
            if (World)
            {
                World->SpawnActor<AProjectile>(
                    ProjectileClass,
                    SocketTransform.GetLocation(),
                    TargetRotation,
                    SpawnParameters
                    );
            }
        }
    }

}

void AGunCharacter::SetHUDCrosshairs(float DeltaTime)
{
    if (!Controller) return;

    // PlayerController = PlayerController == nullptr ? Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0)) : PlayerController;

    HUD = HUD == nullptr ? Cast<AMyHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()) : HUD;

    if (HUD)
    {
        FHUDPackage HUDPackage;
        HUDPackage.CrosshairsCenter = CrosshairsCenter;
        HUDPackage.CrosshairsLeft = CrosshairsLeft;
        HUDPackage.CrosshairsRight = CrosshairsRight;
        HUDPackage.CrosshairsBottom = CrosshairsBottom;
        HUDPackage.CrosshairsTop = CrosshairsTop;
        HUD->SetHUDPackage(HUDPackage);
    }

}


void AGunCharacter::Fire()
{
    FireFromVector(Hit_Target);
}

// Called to bind functionality to input
void AGunCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(FName("Turn"), this, &ThisClass::Turn);
    PlayerInputComponent->BindAxis(FName("Lookup"), this, &ThisClass::Lookup);

    PlayerInputComponent->BindAction(FName("Fire"), IE_Pressed, this, &ThisClass::FireButtonPressed);


    if (!bMoveEnable) return;

    PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ThisClass::MoveForward);

    PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ThisClass::MoveRight);


    PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ThisClass::Jump);
}

