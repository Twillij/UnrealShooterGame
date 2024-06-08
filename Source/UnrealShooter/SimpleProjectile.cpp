#include "SimpleProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

ASimpleProjectile::ASimpleProjectile()
{
	bReplicates = true;

	// Set up the collision component
	USphereComponent* CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionSphere->InitSphereRadius(37.5f);
	CollisionSphere->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	HitCollisionComponent = CollisionSphere;
	SetRootComponent(HitCollisionComponent);
	
	// Set up the mesh component
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(GetRootComponent());

	// Set up the movement component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->SetUpdatedComponent(HitCollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 1500.0f;
	ProjectileMovementComponent->MaxSpeed = 1500.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
}

void ASimpleProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetLocalRole() == ROLE_Authority)
	{
		HitCollisionComponent->OnComponentHit.AddDynamic(this, &ASimpleProjectile::OnProjectileImpact);
	}
}

void ASimpleProjectile::Destroyed()
{
	Super::Destroyed();
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, GetActorLocation(), FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);
}

void ASimpleProjectile::OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		UGameplayStatics::ApplyPointDamage(OtherActor, Damage, NormalImpulse, Hit, GetInstigator()->Controller, this, DamageType);
	}
	Destroy();
}
