// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "Character/GunCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    GunCharacter = Cast<AGunCharacter>(TryGetPawnOwner());
    if (GunCharacter)
    {
        GunCharacterMovement = GunCharacter->GetCharacterMovement();
    }
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);


    if (GunCharacter)
    {
        const FVector Velocity = GunCharacterMovement->Velocity;
        //地面での速度を計算
        GroundSpeed = Velocity.Size2D();

        // ジャンプしているかどうか
        bIsInAir = GunCharacterMovement->IsFalling();

        bIsFiring = GunCharacter->GetIsFiring();
    }
}
