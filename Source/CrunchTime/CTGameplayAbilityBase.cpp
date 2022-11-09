// Fill out your copyright notice in the Description page of Project Settings.


#include "CTGameplayAbilityBase.h"
#include "CTAttributeSet.h"

float UCTGameplayAbilityBase::GetCooldownDuration() const
{
	float coolDownDuration = 0;
	auto coolDownEffect = GetCooldownGameplayEffect();

	if (coolDownEffect)
	{
		GetCooldownGameplayEffect()->DurationMagnitude.GetStaticMagnitudeIfPossible(1, coolDownDuration);
	}
	return coolDownDuration;
}

float UCTGameplayAbilityBase::GetCost() const
{
	
	auto costEffect = GetCostGameplayEffect();
	if (!costEffect)
	{
		return 0;
	}
	float staminaCost = 0;

	for (auto& modifier : GetCostGameplayEffect()->Modifiers)
	{
		if (modifier.Attribute == UCTAttributeSet::GetStaminaAttribute())
		{
			modifier.ModifierMagnitude.GetStaticMagnitudeIfPossible(1, staminaCost);
		}
	}

	return staminaCost;
}

bool UCTGameplayAbilityBase::CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags)
{
	if (Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags))
	{
		UCTGameplayAbilityBase* CDO = Cast<UCTGameplayAbilityBase>(GetClass()->GetDefaultObject());
		if (CDO)
		{
			CDO->onAbilityActivated.Broadcast();
		}
		return true;
	}
	return false;
}

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
