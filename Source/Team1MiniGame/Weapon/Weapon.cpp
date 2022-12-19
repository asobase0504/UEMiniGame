﻿

#include "Weapon.h"

AWeapon::AWeapon()
{
    PrimaryActorTick.bCanEverTick = true;

    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
    WeaponMesh->SetupAttachment(RootComponent);
    SetRootComponent(WeaponMesh);
}

void AWeapon::BeginPlay()
{
    Super::BeginPlay();

}

void AWeapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

