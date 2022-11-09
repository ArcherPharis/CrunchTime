// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCHTIME_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "InGameUI")
	void UpdateHealth(float newHealth, float maxHealth);

	UFUNCTION(BlueprintImplementableEvent, Category = "InGameUI")
	void UpdateStamina(float newStamina, float maxStamina);

	UFUNCTION(BlueprintImplementableEvent)
	void AddNewAbilityEntry(const class UCTGameplayAbilityBase* newAbility);
	
};
