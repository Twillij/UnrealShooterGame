#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class UNREALSHOOTER_API ASimpleProjectile : public AActor
{
	GENERATED_BODY()

public:
	ASimpleProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UShapeComponent* HitCollisionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ProjectileMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* ProjectileMovementComponent;
	
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* ExplosionEffect;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	TSubclassOf<UDamageType> DamageType = UDamageType::StaticClass();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Damage = 10;

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UFUNCTION()
	void OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
