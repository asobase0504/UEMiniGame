// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GunCharacter.generated.h"

#define TRACE_LENGTH 80000.f

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TEAM1MINIGAME_API AGunCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AGunCharacter();

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // インプット　コールバック関数
    void MoveForward(float Value);
    void Turn(float Value);
    void Lookup(float Value);
    void MoveRight(float Value);
    void EquipKeyPressed();
    void FireButtonPressed();

    void TraceUnderCrosshairs(FHitResult& TraceHitResult);

    void FireFromVector(const FVector& HitTarget);

    void SetHUDCrosshairs(float DeltaTime);

    UFUNCTION(BlueprintCallable)
        void Fire();

    UFUNCTION(BlueprintCallable)
        void SetCanFire(bool CanFire) { this->bIsCanFire = CanFire; }

    UFUNCTION(BlueprintCallable)
        void SetIsFiring(bool IsFiring) { this->bIsFiring = IsFiring; }

    UFUNCTION(BlueprintCallable)
        bool GetIsFiring() { return bIsFiring; }

protected:
    virtual void BeginPlay() override;

public:

private:
    class AMyHUD* HUD;
    class AMyPlayerController* PlayerController;

    UPROPERTY(VisibleAnywhere)
        USpringArmComponent* CameraBoom;  //カメラブーム

    UPROPERTY(VisibleAnywhere)
        UCameraComponent* ViewCamera;  //ビューカメラ

    UPROPERTY(VisibleAnywhere)
        UStaticMeshComponent* WeaponMesh;

    UPROPERTY(EditDefaultsOnly)
        bool bMoveEnable;

    UPROPERTY(VisibleAnywhere, Category = "FireFromVector")
        bool bIsFiring;

    UPROPERTY(VisibleAnywhere, Category = "FireFromVector")
        bool bIsCanFire;

    FVector Hit_Target;

    UPROPERTY(EditAnywhere)
        TSubclassOf<class AProjectile> ProjectileClass;

    UPROPERTY(EditAnywhere, Category = "Crosshairs")
        UTexture2D* CrosshairsCenter;

    UPROPERTY(EditAnywhere, Category = "Crosshairs")
        UTexture2D* CrosshairsLeft;

    UPROPERTY(EditAnywhere, Category = "Crosshairs")
        UTexture2D* CrosshairsRight;

    UPROPERTY(EditAnywhere, Category = "Crosshairs")
        UTexture2D* CrosshairsTop;

    UPROPERTY(EditAnywhere, Category = "Crosshairs")
        UTexture2D* CrosshairsBottom;
};
