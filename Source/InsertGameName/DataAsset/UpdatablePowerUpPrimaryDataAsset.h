// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUpPrimaryDataAsset.h"
#include "UpdatablePowerUpPrimaryDataAsset.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class UUpdatablePowerUpPrimaryDataAsset : public UPowerUpPrimaryDataAsset
{
	GENERATED_BODY()

	/** How long  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timer", meta = (AllowPrivateAccess = true))
	float ActiveTime;


public:

	FORCEINLINE float GetActiveTime() const noexcept
	{
		return ActiveTime;
	}
	
};
