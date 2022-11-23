// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MainWeaponProjectileDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API UMainWeaponProjectileDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Gameplay, meta=(ClampMin="0.0",ClampMax="8000.0", AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, Category = Gameplay, meta=(ClampMin="0.0",ClampMax="100.0", AllowPrivateAccess = true))
	float DealDamage;

	UPROPERTY(EditAnywhere, Category = Gameplay, meta=(ClampMin="0.0",ClampMax="10.0", AllowPrivateAccess = true))
	float LifeTime;

public:

	FORCEINLINE float GetSpeed() const noexcept
	{
		return Speed;
	}

	FORCEINLINE float GetDamage() const noexcept
	{
		return DealDamage;
	}

	FORCEINLINE float GetLifetime() const noexcept
	{
		return LifeTime;
	}
};
