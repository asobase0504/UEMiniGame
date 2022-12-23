// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class TEAM1MINIGAME_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
		int32 Score;

	UPROPERTY(BlueprintReadOnly)
		bool IsHit = false;

private:
	UPROPERTY(EditDefaultsOnly, Category = Montages)
		UAnimMontage* HitReactMontage;

	UPROPERTY(EditAnywhere, Category = Sounds)
		USoundBase* HitSound;

	UPROPERTY(VisibleAnywhere)
		float Timer;

public:
	UFUNCTION(BlueprintCallable)
		void GetHit();

};
