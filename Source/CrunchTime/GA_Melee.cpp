// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Melee.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

void UGA_Melee::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	UAbilityTask_PlayMontageAndWait* MontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, MeleeMontage);
	if (MontagePlay)
	{
		MontagePlay->OnBlendOut.AddDynamic(this, &UGA_Melee::MontageFinshed);
		MontagePlay->OnCancelled.AddDynamic(this, &UGA_Melee::MontageFinshed);
		MontagePlay->OnInterrupted.AddDynamic(this, &UGA_Melee::MontageFinshed);
		MontagePlay->OnCompleted.AddDynamic(this, &UGA_Melee::MontageFinshed);
		MontagePlay->ReadyForActivation();
	}
	UAbilityTask_WaitGameplayEvent* WaitComboChange = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, ComboChangeTag, nullptr, false, false);
	if (WaitComboChange)
	{
		WaitComboChange->EventReceived.AddDynamic(this, &UGA_Melee::UpdateCombo);
		WaitComboChange->ReadyForActivation();
	}
}

void UGA_Melee::MontageFinshed()
{
	UE_LOG(LogTemp, Warning, TEXT("Melee has stopped"));
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(),GetCurrentActivationInfo(), false, false);
}

void UGA_Melee::UpdateCombo(FGameplayEventData Payload)
{
	nextComboTag = Payload.EventTag;
	UE_LOG(LogTemp, Warning, TEXT("Getting Tag: %s"), *nextComboTag.ToString());

}
