// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CTGameplayAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCHTIME_API UCTGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GameplayAbilityBase")
	FName GetRandomNameFromTagContainer(const FGameplayTagContainer& container) const;
	
};
