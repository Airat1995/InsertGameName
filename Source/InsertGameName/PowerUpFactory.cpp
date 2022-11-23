// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpFactory.h"

#include "MultiplierPowerUp.h"
#include "TimerAddPowerUp.h"
#include "TimerPowerUpPrimaryDataAsset.h"


UPowerUpFactory* UPowerUpFactory::Make(TObjectPtr<UObject> Parent, TObjectPtr<UScoreCounter> Counter, TObjectPtr<UGlobalTimer> GlobalTimer)
{
	UPowerUpFactory* Factory = NewObject<UPowerUpFactory>(Parent);
	Factory->Timer = GlobalTimer;
	Factory->ScoreCounter = Counter;
	Factory->SpawnParent = Parent;

	return Factory;
}


IPowerUp* UPowerUpFactory::CreatePowerup(const TObjectPtr<UPowerUpPrimaryDataAsset> DataAsset)
{
	IPowerUp* CreatedPowerup = nullptr;
	if(DataAsset.IsA(UScoreMultPowerUpPrimaryDataAsset::StaticClass()))
	{
		UScoreMultPowerUpPrimaryDataAsset* MultPowerUpPrimaryDataAsset = Cast<UScoreMultPowerUpPrimaryDataAsset>(DataAsset);
		CreatedPowerup = UMultiplierPowerUp::Make(SpawnParent, ScoreCounter, MultPowerUpPrimaryDataAsset);
	}
	else if(DataAsset.IsA(UTimerPowerUpPrimaryDataAsset::StaticClass()))
	{
		UTimerPowerUpPrimaryDataAsset* TimerPowerUpPrimaryDataAsset = Cast<UTimerPowerUpPrimaryDataAsset>(DataAsset);
		CreatedPowerup = UTimerAddPowerUp::Make(SpawnParent, Timer, TimerPowerUpPrimaryDataAsset);
	}

	return CreatedPowerup;
}
