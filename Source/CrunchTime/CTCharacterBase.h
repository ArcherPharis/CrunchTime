// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "CTCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStopSprinting);

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "GameplayAbilities")
	void ApplyEffectToSelf(const TSubclassOf<class UGameplayEffect>& effectToApply);
	void BasicAttack();
	void Sprint();
	void StopSprint();
	void Cast();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	void RegenStamina(TSubclassOf<class UGameplayEffect> regenEffect);
	FORCEINLINE class UCTAttributeSet* GetAttributeSet() const { return attributeSet; }
	void SprintDepletedStopSprint();
	UFUNCTION(BlueprintImplementableEvent, Category = "GameplayAbility", meta = (DisplayName = "HealthUpdated"))
	void BP_HealthUpdated(float Health, float healthDelta, float maxHealth);

	UFUNCTION(BlueprintCallable, Category = "GameplayAbility")
	void SpawnCurrentMagic();

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
	TSubclassOf<class UGameplayAbility> CastAbility;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TSubclassOf<class AProjectile> currentMagic;
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	FName magicSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	FGameplayTag BasicAttackCombo;


	UPROPERTY(EditDefaultsOnly, Category = "Character")
	class UHitDetectionComponent* hitDetectionComp;


	void GiveAbility(const TSubclassOf<class UGameplayAbility>& newAbility);

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	float sprintMultiplier = 1.5f;

	void HealthChanged(const FOnAttributeChangeData& ChangedData);

	bool bIsRunning = false;






};
