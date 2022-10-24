// Fill out your copyright notice in the Description page of Project Settings.


#include "CTCrunch.h"
#include "GameframeWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ACTCrunch::ACTCrunch()
{
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	cameraBoom->SetupAttachment(GetRootComponent());
	cameraBoom->bUsePawnControlRotation = true;
	PlayerEye = CreateDefaultSubobject<UCameraComponent>("PlayerEye");
	PlayerEye->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);
}

void ACTCrunch::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACTCrunch::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACTCrunch::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ACTCrunch::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ACTCrunch::Turn);
	PlayerInputComponent->BindAxis("Zoom", this, &ACTCrunch::Zoom);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACTCrunch::Jump);



}

void ACTCrunch::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

void ACTCrunch::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}

void ACTCrunch::LookUp(float value)
{
	AddControllerPitchInput(value);
}

void ACTCrunch::Turn(float value)
{
	AddControllerYawInput(value);
}

void ACTCrunch::Zoom(float value)
{
	if (value == 1)
	{
		cameraBoom->TargetArmLength += -zoomAmount;
	}

	if (value == -1)
	{
		cameraBoom->TargetArmLength += zoomAmount;
	}

}
