// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalTimer.h"
#include "IPowerUp.h"
#include "PowerUpPrimaryDataAsset.h"
#include "ScoreCounter.h"
#include "PowerUpFactory.generated.h"

/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API UPowerUpFactory : public UObject
{

	GENERATED_BODY()
	
public:
	static UPowerUpFactory* Make(TObjectPtr<UObject> Parent, TObjectPtr<UScoreCounter> Counter, TObjectPtr<UGlobalTimer> GlobalTimer);
	IPowerUp* CreatePowerup(const TObjectPtr<UPowerUpPrimaryDataAsset> DataAsset);

private:

	UPROPERTY()
	TObjectPtr<UObject> SpawnParent;

	UPROPERTY()
	TObjectPtr<UGlobalTimer> Timer;

	UPROPERTY()
	TObjectPtr<UScoreCounter> ScoreCounter;
};
