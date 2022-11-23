// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UpdatablePowerUpPrimaryDataAsset.h"
#include "ScoreMultPowerUpPrimaryDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class UScoreMultPowerUpPrimaryDataAsset : public UUpdatablePowerUpPrimaryDataAsset
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Multiplier", meta = (AllowPrivateAccess = true))
	float ScoreMultiplier;

public:

	FORCEINLINE float GetScoreMultiplier() const noexcept
	{
		return ScoreMultiplier;
	}
};
