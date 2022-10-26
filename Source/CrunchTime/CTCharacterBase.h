// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CTCharacterBase.generated.h"

UCLASS()
class CRUNCHTIME_API ACTCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACTCharacterBase();
	void ApplyInitialEffect();
	virtual void PossessedBy(AController* NewController) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "GameplayAbilities")
	void ApplyEffectToSelf(const TSubclassOf<class UGameplayEffect>& effectToApply);
	void BasicAttack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	FORCEINLINE class UCTAttributeSet* GetAttributeSet() const { return attributeSet; }

private:

	
	UPROPERTY()
	class UCT_AbilitySystemComponent* abilitySystemComp;

	UPROPERTY()
	UCTAttributeSet* attributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TSubclassOf<class UGameplayEffect> InitialEffect;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TSubclassOf<class UGameplayAbility> BasicAttackAbility;

	void GiveAbility(const TSubclassOf<class UGameplayAbility>& newAbility);




};
