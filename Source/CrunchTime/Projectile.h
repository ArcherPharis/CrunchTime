// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "Projectile.generated.h"

UCLASS()
class CRUNCHTIME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Projectile")
		float HitEffectMagnitude = 10.f;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		FGameplayTag HitEventTag;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UCapsuleComponent* GetCapsuleComponent() const { return capsuleComponent; }


private:

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	class UProjectileMovementComponent* projectileMovementComp;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	class UParticleSystemComponent* particleSystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	class UCapsuleComponent* capsuleComponent;



};
