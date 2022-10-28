// Fill out your copyright notice in the Description page of Project Settings.


#include "CTCharacterBase.h"
#include "CT_AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CTAttributeSet.h"

// Sets default values
ACTCharacterBase::ACTCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	abilitySystemComp = CreateDefaultSubobject<UCT_AbilitySystemComponent>(TEXT("Ability System Comp"));
	attributeSet = CreateDefaultSubobject<UCTAttributeSet>(TEXT("Attribute Set"));


}

void ACTCharacterBase::ApplyInitialEffect()
{
	ApplyEffectToSelf(InitialEffect);
}

void ACTCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	abilitySystemComp->InitAbilityActorInfo(NewController, this); //can also be done in begin play if you don't care about controller
	GiveAbility(BasicAttackAbility);
	GiveAbility(SprintAbility);


}

// Called when the game starts or when spawned
void ACTCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACTCharacterBase::ApplyEffectToSelf(const TSubclassOf<class UGameplayEffect>& effectToApply)
{
	FGameplayEffectSpecHandle InitialSpec = abilitySystemComp->MakeOutgoingSpec(InitialEffect, -1, abilitySystemComp->MakeEffectContext());
	abilitySystemComp->ApplyGameplayEffectSpecToSelf(*InitialSpec.Data);
}

void ACTCharacterBase::BasicAttack()
{
	FGameplayAbilitySpec* meleeSpec = abilitySystemComp->FindAbilitySpecFromClass(BasicAttackAbility);

	if (meleeSpec->IsActive())
	{
		//do next combo, go to next montage section
	}
	else
	{
		abilitySystemComp->TryActivateAbilityByClass(BasicAttackAbility);
	}

	
}

void ACTCharacterBase::Sprint()
{
	if (GetVelocity().Length() > 0)
	{
		GetCharacterMovement()->MaxWalkSpeed *= sprintMultiplier;
		bIsRunning = true;
		abilitySystemComp->TryActivateAbilityByClass(SprintAbility);
	}
}

void ACTCharacterBase::StopSprint()
{
	if(bIsRunning)
	GetCharacterMovement()->MaxWalkSpeed /= sprintMultiplier;
	bIsRunning = false;
	onStopSprinting.Broadcast();

	
}

// Called every frame
void ACTCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

UAbilitySystemComponent* ACTCharacterBase::GetAbilitySystemComponent() const
{
	return abilitySystemComp;
}

void ACTCharacterBase::RegenStamina(TSubclassOf<class UGameplayEffect> regenEffect)
{
	if (!IsStaminaFull() && !bIsRunning)
	{
		FGameplayEffectContextHandle EffectContext = abilitySystemComp->MakeEffectContext();

		abilitySystemComp->ApplyGameplayEffectToSelf(regenEffect.GetDefaultObject(), -1, EffectContext);
	}
}

void ACTCharacterBase::SprintDepletedStopSprint()
{
	StopSprint();
}

bool ACTCharacterBase::IsStaminaFull()
{
	if (attributeSet->GetStamina() < attributeSet->GetMaxStamina())
	{
		return false;
	}
	return true;
}



void ACTCharacterBase::GiveAbility(const TSubclassOf<class UGameplayAbility>& newAbility)
{
	abilitySystemComp->GiveAbility(FGameplayAbilitySpec(newAbility));
}


