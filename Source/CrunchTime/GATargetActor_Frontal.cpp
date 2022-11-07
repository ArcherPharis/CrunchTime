// Fill out your copyright notice in the Description page of Project Settings.


#include "GATargetActor_Frontal.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbility.h"

AGATargetActor_Frontal::AGATargetActor_Frontal()
{
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	TargetArea = CreateDefaultSubobject<UBoxComponent>("TargetArea");
	TargetArea->SetupAttachment(RootComp);

	TargetArea->SetCollisionResponseToChannels(ECR_Ignore);
	TargetArea->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

void AGATargetActor_Frontal::ConfirmTargetingAndContinue()
{
	TArray<AActor*> OverlappingActors;
	TargetArea->GetOverlappingActors(OverlappingActors);
	
	OverlappingActors.Remove(OwningAbility->GetAvatarActorFromActorInfo()); //this will be whatever casted the ability.
	TargetDataReadyDelegate.Broadcast(UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActorArray(OverlappingActors, false));
}
