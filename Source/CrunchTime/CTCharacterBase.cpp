// Fill out your copyright notice in the Description page of Project Settings.


#include "CTCharacterBase.h"
#include "CT_AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HitDetectionComponent.h"
#include "CTAttributeSet.h"
#include "CTGameplayAbilityBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACTCharacterBase::ACTCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	abilitySystemComp = CreateDefaultSubobject<UCT_AbilitySystemComponent>(TEXT("Ability System Comp"));
	attributeSet = CreateDefaultSubobject<UCTAttributeSet>(TEXT("Attribute Set"));
	hitDetectionComp = CreateDefaultSubobject<UHitDetectionComponent>(TEXT("Hit Detection Component"));
	hitDetectionComp->SetupAttachment(GetMesh());


}

void ACTCharacterBase::ApplyInitialEffect()
{
	for (auto effect : InitialEffects)
	{
		ApplyEffectToSelf(effect);
	}

	
}

void ACTCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	abilitySystemComp->InitAbilityActorInfo(this, this); //can also be done in begin play if you don't care about controller



}

void ACTCharacterBase::SetIsAiming(bool aiming)
{
	bIsAiming = aiming;

	GetCharacterMovement()->bOrientRotationToMovement = !bIsAiming;
	bUseControllerRotationYaw = bIsAiming;

}

// Called when the game starts or when spawned
void ACTCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	ApplyInitialEffect();
	GiveAbility(BasicAttackAbility);
	GiveAbility(SprintAbility);

	for (auto& abilityKeyValuePair : InitialAbilities)
	{
		GiveAbility(abilityKeyValuePair.Value, static_cast<int>(abilityKeyValuePair.Key), true);
	}
}

void ACTCharacterBase::ApplyEffectToSelf(const TSubclassOf<class UGameplayEffect>& effectToApply)
{
	FGameplayEffectSpecHandle InitialSpec = abilitySystemComp->MakeOutgoingSpec(effectToApply, -1, abilitySystemComp->MakeEffectContext());
	abilitySystemComp->ApplyGameplayEffectSpecToSelf(*InitialSpec.Data);
}

void ACTCharacterBase::BasicAttack()
{
	FGameplayAbilitySpec* meleeSpec = abilitySystemComp->FindAbilitySpecFromClass(BasicAttackAbility);

	if (meleeSpec->IsActive())
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, BasicAttackCombo, FGameplayEventData());
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



void ACTCharacterBase::GiveAbility(const TSubclassOf<class UGameplayAbility>& newAbility, int inputID, bool broadCast)
{
	
	FGameplayAbilitySpecHandle AbilitySpecHandle = abilitySystemComp->GiveAbility(FGameplayAbilitySpec(newAbility, 1, inputID));

	if (broadCast)
	{
		onAbilityAdded.Broadcast(Cast<UCTGameplayAbilityBase>(GetAbilitySystemComponent()->FindAbilitySpecFromHandle(AbilitySpecHandle)->Ability));
	}
}


