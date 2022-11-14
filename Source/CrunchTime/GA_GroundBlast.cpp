// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_GroundBlast.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "CTCharacterBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "CTGameplayAbilityBase.h"

void UGA_GroundBlast::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{


	if (!K2_CheckAbilityCost() || !K2_CheckAbilityCooldown())
	{
		return;
	}


	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	UAbilityTask_PlayMontageAndWait* CastStartMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, castMontage);

	if (CastStartMontageTask)
	{
		CastStartMontageTask->OnBlendOut.AddDynamic(this, &UGA_GroundBlast::CastStartMontageEnded);
		CastStartMontageTask->OnCancelled.AddDynamic(this, &UGA_GroundBlast::CastStartMontageEnded);
		CastStartMontageTask->OnInterrupted.AddDynamic(this, &UGA_GroundBlast::CastStartMontageEnded);
		CastStartMontageTask->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* WaitStartTargettingTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, startTargettingTags, nullptr, false, false);

	if (WaitStartTargettingTask)
	{
		WaitStartTargettingTask->EventReceived.AddDynamic(this, &UGA_GroundBlast::StartTargetting);
		WaitStartTargettingTask->ReadyForActivation();
	}
}

void UGA_GroundBlast::StartTargetting(FGameplayEventData Payload)
{

	GetAvatarAsCharacter()->SetIsAiming(true);


	UAbilityTask_WaitTargetData* WaitTargettingTask = UAbilityTask_WaitTargetData::WaitTargetData(this, NAME_None, EGameplayTargetingConfirmation::UserConfirmed, targetActorClass);
	//this is just wait target data
	if (WaitTargettingTask)
	{
		WaitTargettingTask->ValidData.AddDynamic(this, &UGA_GroundBlast::TargetAcquired);
		WaitTargettingTask->Cancelled.AddDynamic(this, &UGA_GroundBlast::TargettingCanceled);
		WaitTargettingTask->ReadyForActivation();

		AGameplayAbilityTargetActor* TargetActorSpawned;
		WaitTargettingTask->BeginSpawningActor(this, targetActorClass, TargetActorSpawned);

		TargetActorSpawned->SetOwner(GetAvatarActorFromActorInfo());
		WaitTargettingTask->FinishSpawningActor(this, TargetActorSpawned);
	}
}

void UGA_GroundBlast::CastStartMontageEnded()
{
	K2_EndAbility();

}

void UGA_GroundBlast::TargetAcquired(const FGameplayAbilityTargetDataHandle& Data)
{
	K2_CommitAbility();
	K2_ApplyGameplayEffectSpecToTarget(MakeOutgoingGameplayEffectSpec(effect), Data);
	LaunchAllActorInTargetData(Data, FVector::UpVector, blastSpeed);

	FVector blastLoc = Data.Get(1)->GetEndPoint();

	UAbilityTask_PlayMontageAndWait* CastMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, castMontageDone);

	if (CastMontageTask)
	{
		CastMontageTask->OnBlendOut.AddDynamic(this, &UGA_GroundBlast::CastStartMontageEnded);
		CastMontageTask->OnCancelled.AddDynamic(this, &UGA_GroundBlast::CastStartMontageEnded);
		CastMontageTask->OnInterrupted.AddDynamic(this, &UGA_GroundBlast::CastStartMontageEnded);
		CastMontageTask->OnCompleted.AddDynamic(this, &UGA_GroundBlast::CastStartMontageEnded);
		CastMontageTask->ReadyForActivation();
	}
	FGameplayCueParameters params;
	params.Location = blastLoc;
	//GetAbilitySystemComponentFromActorInfo()->AddGameplayCue(BlastCueTag, params);

	
}

void UGA_GroundBlast::TargettingCanceled(const FGameplayAbilityTargetDataHandle& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Target Canceled."));
	K2_EndAbility();
	
}

void UGA_GroundBlast::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	GetAvatarAsCharacter()->SetIsAiming(false);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
