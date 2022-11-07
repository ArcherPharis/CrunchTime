// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATargetActor_Frontal.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCHTIME_API AGATargetActor_Frontal : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
		AGATargetActor_Frontal();

private:
	virtual void ConfirmTargetingAndContinue() override;

	UPROPERTY(EditDefaultsOnly, Category = "TargetActor")
	class USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly, Category = "TargetActor")
	class UBoxComponent* TargetArea;
	
};
