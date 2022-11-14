// Fill out your copyright notice in the Description page of Project Settings.


#include "GATargetActor_Groundblast.h"
#include "Abilities/GameplayAbility.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

AGATargetActor_Groundblast::AGATargetActor_Groundblast()
{
	PrimaryActorTick.bCanEverTick = true; 
	targetArea = CreateDefaultSubobject<USphereComponent>(TEXT("TargetArea"));
	SetRootComponent(targetArea);
	targetArea->SetCollisionResponseToAllChannels(ECR_Ignore);
	targetArea->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AGATargetActor_Groundblast::ConfirmTargetingAndContinue()
{
	TArray<AActor*> OverlappingActors;
	targetArea->GetOverlappingActors(OverlappingActors);
	OverlappingActors.Remove(OwningAbility->GetAvatarActorFromActorInfo());
	FGameplayAbilityTargetData_ActorArray* TargetActors = new FGameplayAbilityTargetData_ActorArray;
	for (auto target : OverlappingActors)
	{
		TargetActors->TargetActorArray.Add(target);
	}

	FGameplayAbilityTargetData_LocationInfo* LocInfo = new FGameplayAbilityTargetData_LocationInfo;
	LocInfo->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	LocInfo->TargetLocation.LiteralTransform = GetActorTransform();


	FGameplayAbilityTargetDataHandle handle;
	handle.Add(TargetActors);
	handle.Add(LocInfo);

	//same thing
	//UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActorArray(OverlappingActors, false);

	TargetDataReadyDelegate.Broadcast(handle);
}

void AGATargetActor_Groundblast::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector ViewLoc;
	FRotator ViewRot;
	GetOwner()->GetActorEyesViewPoint(ViewLoc, ViewRot);
	FHitResult traceResult;
	if (GetWorld()->LineTraceSingleByChannel(traceResult, ViewLoc, ViewLoc + ViewRot.Vector() * pickDistance, ECC_Visibility))
	{
		SetActorLocation(traceResult.ImpactPoint);
	}
}

