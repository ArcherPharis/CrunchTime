// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Cast.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystemBlueprintLibrary.h"

void UGA_Cast::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilityTask_PlayMontageAndWait* MontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, CastMontage);
	if (MontagePlay)
	{
		//MontagePlay->OnBlendOut.AddDynamic(this, &UGA_Cast::MontageFinshed);
		//MontagePlay->OnCancelled.AddDynamic(this, &UGA_Cast::MontageFinshed);
		//MontagePlay->OnInterrupted.AddDynamic(this, &UGA_Cast::MontageFinshed);
		//MontagePlay->OnCompleted.AddDynamic(this, &UGA_Cast::MontageFinshed);
		MontagePlay->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* WaitExplosion = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, ExplosionTag, nullptr, false, false);
	if (WaitExplosion)
	{
		WaitExplosion->EventReceived.AddDynamic(this, &UGA_Cast::ApplyExplosionDamage);
		WaitExplosion->ReadyForActivation();
	}
}

void UGA_Cast::ApplyExplosionDamage(FGameplayEventData Payload)
{
	UE_LOG(LogTemp, Warning, TEXT("Damage is ready to be applied."));


	if (Payload.TargetData.Num() == 0) return;

	for (TSharedPtr<FGameplayAbilityTargetData>& data : Payload.TargetData.Data)
	{
		for (TWeakObjectPtr<AActor>& actorWeakPtr : data->GetActors())
		{
			AActor* HitTarget = actorWeakPtr.Get();

		}
	}


	FGameplayEffectSpecHandle handle = MakeOutgoingGameplayEffectSpec(hitEffect, Payload.EventMagnitude);
	K2_ApplyGameplayEffectSpecToTarget(handle, Payload.TargetData);
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void UGA_Cast::MontageFinshed()
{
	UE_LOG(LogTemp, Warning, TEXT("Cast finished"));
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}
