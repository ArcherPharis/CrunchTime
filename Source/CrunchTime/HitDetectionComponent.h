// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameplayEffectTypes.h"
#include "HitDetectionComponent.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCHTIME_API UHitDetectionComponent : public UCapsuleComponent
{
	GENERATED_BODY()

public:
	UHitDetectionComponent();

	UFUNCTION(BlueprintCallable, Category = "HitDetection")
	FORCEINLINE	void SetEffectMagnitude(float newMagnitude) { AttackEffectMagnitutde = newMagnitude; }

private:
	UFUNCTION()
	void Overlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep);

	
	UPROPERTY(EditAnywhere)
	FGameplayTag HitEventTag;

	float AttackEffectMagnitutde = 1;


};
