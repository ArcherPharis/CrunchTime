// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Sprint.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCHTIME_API UGA_Sprint : public UGameplayAbility
{
	GENERATED_BODY()

public:

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void StoppedSprinting();

	UPROPERTY(EditDefaultsOnly, Category = "Sprint")
	TSubclassOf<class UGameplayEffect> SprintRegenEffect;

	class ACTCharacterBase* character;
	
};
