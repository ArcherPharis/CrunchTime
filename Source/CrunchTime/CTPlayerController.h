// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayEffectTypes.h"
#include "CTPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCHTIME_API ACTPlayerController : public APlayerController
{
	GENERATED_BODY()


protected:
	virtual void OnPossess(APawn* InPawn) override;

public:


private:
	class ACTCrunch* Crunch;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UInGameUI> InGameUIClass;

	UInGameUI* inGameUI;

	void HealthUpdated(const FOnAttributeChangeData& AttributeData);

	void StaminaUpdated(const FOnAttributeChangeData& AttributeData);
	
};
