// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon.h"
#include "ArsenalComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INSERTGAMENAME_API UArsenalComponent : public UActorComponent
{
	GENERATED_BODY()

	// Sets default values for this component's properties
	UArsenalComponent();

public:	

	static UArsenalComponent* Make(UObject* Parent, const APlayerController* const Controller, UAnimInstance* const AnimInstance);
	
	UFUNCTION(BlueprintCallable)
	void WearNextWeapon();

	UFUNCTION(BlueprintCallable)
	void WearPreviousWeapon();

	UFUNCTION(BlueprintCallable)
	void WearWeaponIndex(int newWeaponIndex);

	UFUNCTION(BlueprintCallable)
	void AttachNewWeapon(AWeapon* newWeapon);

	UFUNCTION(BlueprintCallable)
	void StartFiring();

	UFUNCTION(BlueprintCallable)
	void StopFiring();

protected:	

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons")
	TArray<AWeapon*> Weapons;

	void ActivateCurrentWeapon(bool activate);
	
private:

	const APlayerController* PlayerController;
	UAnimInstance* Anim;
	AWeapon* CurrentWeapon;
	int CurrentWeaponIndex;
};
