// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScanHitWeaponDataAsset.h"
#include "Weapon.h"
#include "ScanHitWeapon.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INSERTGAMENAME_API AScanHitWeapon : public AWeapon
{
	GENERATED_BODY()

	// Sets default values for this component's properties
	AScanHitWeapon();
	
protected:

	virtual void Firing() override;

	virtual void AttachWeapon(const APlayerController* const Controller, UAnimInstance* const AnimInstance) override;

	UScanHitWeaponDataAsset* ScanHitWeaponDataAsset;

private:

	static constexpr int HIT_DISTANCE = 100000;
};
