// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "CTAbilityTypes.h"
#include "CTCharacterBase.generated.h"


class UCTGameplayAbilityBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStopSprinting);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityAdded, UCTGameplayAbilityBase*, newAbility);

UCLASS()
class CRUNCHTIME_API ACTCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACTCharacterBase();
	void ApplyInitialEffect();
	virtual void PossessedBy(AController* NewController) override;
	UFUNCTION(BlueprintCallable, Category = "Character")
	bool CharacterIsSprinting() const { return bIsRunning; }

	FOnStopSprinting onStopSprinting;
	FOnAbilityAdded onAbilityAdded;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "GameplayAbilities")
	void ApplyEffectToSelf(const TSubclassOf<class UGameplayEffect>& effectToApply);
	void BasicAttack();
	void Sprint();
	void StopSprint();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	void RegenStamina(TSubclassOf<class UGameplayEffect> regenEffect);
	FORCEINLINE class UCTAttributeSet* GetAttributeSet() const { return attributeSet; }
	void SprintDepletedStopSprint();

private:
	bool IsStaminaFull();
	
	UPROPERTY()
	class UCT_AbilitySystemComponent* abilitySystemComp;

	UPROPERTY()
	UCTAttributeSet* attributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TArray<TSubclassOf<class UGameplayEffect>> InitialEffects;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TSubclassOf<class UGameplayAbility> BasicAttackAbility;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TSubclassOf<class UGameplayAbility> SprintAbility;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TMap<ECTAbilityInputID, TSubclassOf<UGameplayAbility>> InitialAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	FGameplayTag BasicAttackCombo;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
		class UHitDetectionComponent* hitDetectionComp;


	void GiveAbility(const TSubclassOf<class UGameplayAbility>& newAbility, int inputID = -1, bool broadCast = false);

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	float sprintMultiplier = 1.5f;



	bool bIsRunning = false;






};
