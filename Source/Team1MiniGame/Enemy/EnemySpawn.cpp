// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawn.h"
#include "Team1MiniGame/Enemy/Enemy.h"

// Sets default values
AEnemySpawn::AEnemySpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawn::BeginPlay()
{
	Super::BeginPlay();
	
   SpawnTimer = FMath::RandRange(SpawnTimeMin, SpawnTimeMax);
  }

// Called every frame
void AEnemySpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    
	Timer += DeltaTime;

    if(Timer>= SpawnTimer)
    {
        SpawnEnemy();
        Timer = 0.f;

        FMath::RandRange(SpawnTimeMin, SpawnTimeMax);
    }
}

void AEnemySpawn::SpawnEnemy()
{
    UWorld* World = GetWorld();
    if (World && EnemyArray.Num() > 0)
    {
        FVector Location = GetActorLocation();
        Location.X += FMath::RandRange(SpawnRangeMin.X, SpawnRangeMax.X);
        Location.Y += FMath::RandRange(SpawnRangeMin.Y, SpawnRangeMax.Y);

        const int32 Selection = FMath::RandRange(0, EnemyArray.Num() - 1);

        World->SpawnActor<AEnemy>(EnemyArray[Selection], Location, GetActorRotation());
    }
}

