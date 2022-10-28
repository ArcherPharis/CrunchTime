// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Sprint.h"
#include "CTCharacterBase.h"
#include "Kismet/GameplayStatics.h"



void UGA_Sprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	character = Cast<ACTCharacterBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	character->onStopSprinting.AddDynamic(this, &UGA_Sprint::StoppedSprinting);
}

void UGA_Sprint::StoppedSprinting()
{
	UE_LOG(LogTemp, Warning, TEXT("We stopped running, event recieved."));
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
	character->RegenStamina(SprintRegenEffect);
}

