// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawn.generated.h"

UCLASS()
class TEAM1MINIGAME_API AEnemySpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();
private:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AEnemy>> EnemyArray;

	UPROPERTY(VisibleAnywhere)
		float Timer;

	UPROPERTY(EditAnywhere)
		float SpawnTimeMin;

	UPROPERTY(EditAnywhere)
		float SpawnTimeMax;

	UPROPERTY(EditAnywhere)
		FVector SpawnRangeMin;

	UPROPERTY(EditAnywhere)
		FVector SpawnRangeMax;

	UPROPERTY(VisibleAnywhere)
	float SpawnTimer;
};
