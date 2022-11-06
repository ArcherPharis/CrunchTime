// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Cast.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCHTIME_API UGA_Cast : public UGameplayAbility
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;


	UPROPERTY(EditDefaultsOnly, Category = "Casting")
	UAnimMontage* CastMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Casting")
	FGameplayTag ExplosionTag;

	UFUNCTION()
	void ApplyExplosionDamage(FGameplayEventData Payload);

	UFUNCTION()
	void MontageFinshed();

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	TSubclassOf<UGameplayEffect> hitEffect;
	
};
