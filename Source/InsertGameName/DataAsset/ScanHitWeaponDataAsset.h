// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponDataAsset.h"
#include "ScanHitWeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API UScanHitWeaponDataAsset : public UWeaponDataAsset
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float Damage;

public:

	FORCEINLINE float GetDamage() const noexcept
	{
		return Damage;
	}
	
};
