// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATargetActor_Groundblast.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCHTIME_API AGATargetActor_Groundblast : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	AGATargetActor_Groundblast();

private:
	virtual void ConfirmTargetingAndContinue() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "GroundPick")
	float pickDistance = 5000.f;
	UPROPERTY(EditDefaultsOnly, Category = "GroundPick")
	class USphereComponent* targetArea;
	
};
