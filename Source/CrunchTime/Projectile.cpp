// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystem.h"
#include "AbilitySystemBlueprintLibrary.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitCapsule"));
	SetRootComponent(capsuleComponent);
	projectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Comp"));
	particleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System"));
	particleSystemComponent->SetupAttachment(capsuleComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

