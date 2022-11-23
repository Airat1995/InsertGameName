// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUpPrimaryDataAsset.h"
#include "TimerPowerUpPrimaryDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class UTimerPowerUpPrimaryDataAsset : public UPowerUpPrimaryDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power UP Value", meta=( AllowPrivateAccess = true))
	float TimerAdd;

public:

	FORCEINLINE float GetTimerAdd() const noexcept
	{
		return TimerAdd;
	}
	
};
