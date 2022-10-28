// Fill out your copyright notice in the Description page of Project Settings.


#include "CTPlayerController.h"
#include "CTCrunch.h"
#include "CTAttributeSet.h"
#include "InGameUI.h"

void ACTPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InGameUIClass)
	{
		inGameUI = CreateWidget<UInGameUI>(this, InGameUIClass);
		inGameUI->AddToViewport();
	}

	Crunch = Cast<ACTCrunch>(InPawn);

	if (Crunch)
	{
		Crunch->GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(Crunch->GetAttributeSet()->GetHealthAttribute()).AddUObject(this, &ACTPlayerController::HealthUpdated);
		Crunch->GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(Crunch->GetAttributeSet()->GetStaminaAttribute()).AddUObject(this, &ACTPlayerController::StaminaUpdated);
		Crunch->ApplyInitialEffect();
	}

}

void ACTPlayerController::HealthUpdated(const FOnAttributeChangeData& AttributeData)
{
	inGameUI->UpdateHealth(AttributeData.NewValue, Crunch->GetAttributeSet()->GetMaxHealth());



}

void ACTPlayerController::StaminaUpdated(const FOnAttributeChangeData& AttributeData)
{
	inGameUI->UpdateStamina(AttributeData.NewValue, Crunch->GetAttributeSet()->GetMaxStamina());
	if (Crunch->GetAttributeSet()->GetStamina() == 0)
	{
		Crunch->SprintDepletedStopSprint();
	}
}
