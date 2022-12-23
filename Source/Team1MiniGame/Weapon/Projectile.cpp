
#include "Projectile.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
#include "Team1MiniGame/Enemy/Enemy.h"

AProjectile::AProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    SetRootComponent(CollisionBox);
    CollisionBox->SetCollisionObjectType(ECC_WorldDynamic);
    CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    CollisionBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
    CollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->bRotationFollowsVelocity = true;

}

void AProjectile::BeginPlay()
{
    Super::BeginPlay();

    CollisionBox->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);

    if (Tracer)
    {
        TracerComponent = UGameplayStatics::SpawnEmitterAttached(
            Tracer,
            CollisionBox,
            FName(),
            GetActorLocation(),
            GetActorRotation(),
            EAttachLocation::KeepWorldPosition
        );
    }
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    FVector NormalImpulse, const FHitResult& Hit)
{
    auto Enemy = Cast<AEnemy>(OtherActor);
    if(Enemy)
    {
        Enemy->GetHit();
    }

    if (ImpactParticle)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, GetTransform());

        if (ImpactSound)
        {
            UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, GetActorLocation());
        }
    }
    Destroy();
}

void AProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

