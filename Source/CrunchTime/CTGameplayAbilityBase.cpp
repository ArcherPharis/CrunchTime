// Fill out your copyright notice in the Description page of Project Settings.


#include "CTGameplayAbilityBase.h"

FName UCTGameplayAbilityBase::GetRandomNameFromTagContainer(const FGameplayTagContainer& container) const
{
	int tagCount = container.Num();

	if (tagCount == 0)
	{
		return NAME_None;

	}
	int comboPickIndex = FMath::RandRange(0, tagCount - 1);

	FGameplayTag pickedTag = container.GetByIndex(comboPickIndex);
	FGameplayTag parentTag = pickedTag.RequestDirectParent();

	FString TagStr = pickedTag.ToString();
	FString ParentStr = parentTag.ToString() + ".";

	TagStr.RemoveAt(0, ParentStr.Len());

	return FName(TagStr);
}
