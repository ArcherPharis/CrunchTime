// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CTCharacterBase.h"
#include "CTCrunch.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCHTIME_API ACTCrunch : public ACTCharacterBase
{
	GENERATED_BODY()

public:
	ACTCrunch();

	
;	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere, Category = "Crunch")
	class USpringArmComponent* cameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Crunch")
	float zoomAmount = 5.0f;

	UPROPERTY(VisibleAnywhere, Category = "Crunch")
	FVector2D ZoomRange{300.f, 1000.f};

	UPROPERTY(VisibleAnywhere, Category = "Crunch")
	class UCameraComponent* PlayerEye;



	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);
	void LookUp(float value);
	void Turn(float value);
	void Zoom(float value);

};

