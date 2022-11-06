// Fill out your copyright notice in the Description page of Project Settings.


#include "StickyFireball.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/CapsuleComponent.h"

void AStickyFireball::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AStickyFireball::OnHit);
}



void AStickyFireball::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{//temporary, this is NOT an OnHit, change to a function that will fire after a timer...
	victim = OtherActor;
	FGameplayEventData eventData;
	FGameplayAbilityTargetDataHandle TargetDataInit = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(OtherActor);
	eventData.TargetData = TargetDataInit;
	eventData.EventMagnitude = HitEffectMagnitude;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), HitEventTag, eventData);
	GetWorldTimerManager().SetTimer(explosionTimerHandle, this, &AStickyFireball::Explode, explosionTimer, false);
	
	
	
}

void AStickyFireball::Explode()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion, GetActorLocation(), FRotator::ZeroRotator, FVector3d(5.0f));

	if (victim)
	{
		FGameplayEventData eventData;
		FGameplayAbilityTargetDataHandle TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(victim);
		eventData.TargetData = TargetData;
		eventData.EventMagnitude = ExplosionEffectMagnitude;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), ExplosionEventTag, eventData);
	}
	Destroy();
}
