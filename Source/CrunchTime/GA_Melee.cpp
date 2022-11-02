// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Melee.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
<<<<<<< Updated upstream
=======
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
=======
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

	//for (TSharedPtr<FGameplayAbilityTargetData>& data : Payload.TargetData.Data)
	//{
	//	for (TWeakObjectPtr<AActor>& actorWeakPtr : data->GetActors())
	//	{
	//		AActor* HitTarget = actorWeakPtr.Get();
	//		
	//	}
	//}

	ACharacter* Avatar = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	Avatar->GetCharacterMovement()->AddImpulse(GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitPushSpeed * Payload.EventMagnitude, true);


	TArray<AActor*> TargetActors = UAbilitySystemBlueprintLibrary::GetActorsFromTargetData(Payload.TargetData, 0);


	for (AActor*& TargetActor : TargetActors)
	{
		ACharacter* TargetAsCharacter = Cast<ACharacter>(TargetActor);

		if (TargetAsCharacter)
		{
			TargetAsCharacter->GetCharacterMovement()->AddImpulse(GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitPushSpeed * Payload.EventMagnitude, true);
		}
	}


	FGameplayEffectSpecHandle handle = MakeOutgoingGameplayEffectSpec(hitEffect, Payload.EventMagnitude);
	handle.Data.Get()->SetContext(Payload.ContextHandle);
	handle.Data.Get()->GetContext().IsValid();
	handle.Data.Get()->GetContext().GetInstigatorAbilitySystemComponent();
	K2_ApplyGameplayEffectSpecToTarget(handle, Payload.TargetData);



	//K2_ApplyGameplayEffectSpecToOwner(handle);



	


}

>>>>>>> Stashed changes
void UGA_Melee::UpdateCombo(FGameplayEventData Payload)
{
	nextComboTag = Payload.EventTag;
	UE_LOG(LogTemp, Warning, TEXT("Getting Tag: %s"), *nextComboTag.ToString());

}
