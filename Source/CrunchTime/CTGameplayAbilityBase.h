// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CTGameplayAbilityBase.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityCommited);

/**
 * 
 */
UCLASS()
class CRUNCHTIME_API UCTGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GameplayAbilityBase")
	float GetCooldownDuration() const;

	UFUNCTION(BlueprintCallable, Category = "GameplayAbilityBase")
	float GetCost() const;

	UFUNCTION(BlueprintCallable, Category = "GameplayAbilityBase")
	FORCEINLINE UTexture2D* GetIcon() const { return AbilityIcon; }

	UPROPERTY(BlueprintAssignable, Category = "GameplayAbilityBase")
	FOnAbilityCommited onAbilityActivated;

protected:
	virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) override;


private:
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbilityBase")
	UTexture2D* AbilityIcon;

public:
	UFUNCTION(BlueprintCallable, Category = "GameplayAbilityBase")
	FName GetRandomNameFromTagContainer(const FGameplayTagContainer& container) const;
	
};
