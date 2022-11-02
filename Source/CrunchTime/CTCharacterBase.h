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

	UFUNCTION(BlueprintImplementableEvent, Category = "GameplayAbility", meta = (DisplayName = "HealthUpdated"))
	void BP_HealthUpdated(float Health, float healthDelta, float maxHealth);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	FORCEINLINE class UCTAttributeSet* GetAttributeSet() const { return attributeSet; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	UAnimMontage* hitReactMontage;

private:

	
	UPROPERTY()
	class UCT_AbilitySystemComponent* abilitySystemComp;

	UPROPERTY()
	UCTAttributeSet* attributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TSubclassOf<class UGameplayEffect> InitialEffect;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TSubclassOf<class UGameplayAbility> BasicAttackAbility;

<<<<<<< Updated upstream
	void GiveAbility(const TSubclassOf<class UGameplayAbility>& newAbility);

=======
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TSubclassOf<class UGameplayAbility> SprintAbility;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	FGameplayTag BasicAttackCombo;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	class UHitDetectionComponent* hitDetectionComp;





	void GiveAbility(const TSubclassOf<class UGameplayAbility>& newAbility);

	void HealthChanged(const FOnAttributeChangeData& ChangedData);

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	float sprintMultiplier = 1.5f;



	bool bIsRunning = false;



>>>>>>> Stashed changes



};
