// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class TEAM1MINIGAME_API AWeapon : public AActor
{
    GENERATED_BODY()

public:
    AWeapon();
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;


public:

private:
    //UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
    //    USkeletalMeshComponent* WeaponMesh;
    UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
        UStaticMeshComponent* WeaponMesh;


    TSubclassOf<class AProjectile> ProjectileClass;
};
