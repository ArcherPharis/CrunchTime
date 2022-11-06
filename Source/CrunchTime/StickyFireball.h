// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "StickyFireball.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCHTIME_API AStickyFireball : public AProjectile
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	class UParticleSystem* explosion;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float ExplosionEffectMagnitude = 10.f;
	UPROPERTY(EditAnywhere, Category = "Projectile")
	FGameplayTag ExplosionEventTag;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float explosionTimer = 0.5f;

	FTimerHandle explosionTimerHandle;

	AActor* victim;

	void Explode();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
