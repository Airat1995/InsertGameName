// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalTimer.h"
#include "IUsablePowerUp.h"
#include "UObject/Object.h"
#include "TimerPowerUpPrimaryDataAsset.h"
#include "TimerAddPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API UTimerAddPowerUp : public UObject, public IIUsablePowerUp
{
	GENERATED_BODY()

public:
	static UTimerAddPowerUp* Make(TObjectPtr<UObject> Parent, TObjectPtr<UGlobalTimer> Timer, TObjectPtr<UTimerPowerUpPrimaryDataAsset> DataAsset);
	
	virtual void Use() override;

protected:

	UPROPERTY()
	TObjectPtr<UGlobalTimer> Timer;

private:
	float TimeToAdd;
};
