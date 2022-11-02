// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Melee.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystemBlueprintLibrary.h"

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

	UAbilityTask_WaitGameplayEvent* WaitCommitChange = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, ComboCommitTag, nullptr, false, false);
	if (WaitCommitChange)
	{
		WaitCommitChange->EventReceived.AddDynamic(this, &UGA_Melee::ComboCommit);
		WaitCommitChange->ReadyForActivation();
	}
	UAbilityTask_WaitGameplayEvent* WaitHit = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, HitTag, nullptr, false, false);
	if (WaitHit)
	{
		WaitHit->EventReceived.AddDynamic(this, &UGA_Melee::Hit);
		WaitHit->ReadyForActivation();
	}
}

void UGA_Melee::MontageFinshed()
{
	UE_LOG(LogTemp, Warning, TEXT("Melee has stopped"));
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(),GetCurrentActivationInfo(), false, false);
}

void UGA_Melee::ComboCommit(FGameplayEventData Payload)
{

	if (NextComboSectionName == "")
	{
		return;
	}

	USkeletalMeshComponent* mesh = GetOwningComponentFromActorInfo();

	if (mesh)
	{
		UAnimInstance* animbp = mesh->GetAnimInstance();

		if (animbp->Montage_GetCurrentSection() == NextComboSectionName)
		{
			return;
		}



		if (animbp)
		{
			animbp->Montage_SetNextSection(animbp->Montage_GetCurrentSection(), NextComboSectionName, animbp->GetCurrentActiveMontage());
			
		}
	}

}

void UGA_Melee::Hit(FGameplayEventData Payload)
{


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



	//K2_ApplyGameplayEffectSpecToOwner(handle);



	


}

void UGA_Melee::UpdateCombo(FGameplayEventData Payload)
{
	FGameplayTag nextComboTag = Payload.EventTag;
	int tagCount = Payload.TargetTags.Num();

	if (tagCount == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No next combo"));
		NextComboSectionName = "";
		return;

	}
	int comboPickIndex = FMath::RandRange(0, tagCount - 1);

	FGameplayTag pickedTag = Payload.TargetTags.GetByIndex(comboPickIndex);
	FGameplayTag parentTag = pickedTag.RequestDirectParent();

	FString TagStr = pickedTag.ToString();
	FString ParentStr = parentTag.ToString() + ".";

	TagStr.RemoveAt(0, ParentStr.Len());

	NextComboSectionName = FName(TagStr);

	UE_LOG(LogTemp, Warning, TEXT("Getting Tag: %s"), *NextComboSectionName.ToString());

}
