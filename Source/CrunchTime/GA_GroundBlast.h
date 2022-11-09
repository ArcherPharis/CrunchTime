// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CTGameplayAbilityBase.h"
#include "GA_GroundBlast.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCHTIME_API UGA_GroundBlast : public UCTGameplayAbilityBase
{
	GENERATED_BODY()

private:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	

	UPROPERTY(EditDefaultsOnly, Category = "GroundBlast")
	UAnimMontage* castMontage;

	UPROPERTY(EditDefaultsOnly, Category = "GroundBlast")
	FGameplayTag startTargettingTags;

	UPROPERTY(EditDefaultsOnly, Category = "GroundBlast")
	TSubclassOf<class AGameplayAbilityTargetActor> targetActorClass;

	UFUNCTION()
	void StartTargetting(FGameplayEventData Payload);

	UFUNCTION()
	void CastStartMontageEnded();
	
	UFUNCTION()
	void TargetAcquired(const FGameplayAbilityTargetDataHandle& Data);

	UFUNCTION()
	void TargettingCanceled(const FGameplayAbilityTargetDataHandle& Data);

};
