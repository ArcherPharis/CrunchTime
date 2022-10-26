// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Melee.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCHTIME_API UGA_Melee : public UGameplayAbility
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	UAnimMontage* MeleeMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	FGameplayTag ComboChangeTag;

	FGameplayTag nextComboTag;

	UFUNCTION()
	void MontageFinshed();

	UFUNCTION()
	void UpdateCombo(FGameplayEventData Payload); //payload is just all the info from the event.
};
