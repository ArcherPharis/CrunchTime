// Fill out your copyright notice in the Description page of Project Settings.


#include "HitDetectionComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

UHitDetectionComponent::UHitDetectionComponent()
{
	OnComponentBeginOverlap.AddDynamic(this, &UHitDetectionComponent::Overlapped);


}


void UHitDetectionComponent::Overlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep)
{
	

	if (OtherActor != GetOwner())
	{
		FGameplayEventData eventData;
		FGameplayAbilityTargetDataHandle TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(OtherActor);
		eventData.TargetData = TargetData;
		eventData.EventMagnitude = AttackEffectMagnitutde;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), HitEventTag, eventData);

	}

}
