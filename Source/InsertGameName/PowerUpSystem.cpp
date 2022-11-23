// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpSystem.h"

UPowerUpSystem* UPowerUpSystem::Make(TObjectPtr<UObject> Parent, TObjectPtr<UGlobalTimer> Timer, TObjectPtr<UScoreCounter> ScoreCounter)
{
	UPowerUpSystem* PowerUpSystem = NewObject<UPowerUpSystem>(Parent);
	PowerUpSystem->Factory = UPowerUpFactory::Make(Parent, ScoreCounter, Timer);
	PowerUpSystem->UpdatablePowerUps.Empty();
	PowerUpSystem->AppliedPowerUps.Empty();

	return PowerUpSystem;
}

UPowerUpSystem::~UPowerUpSystem()
{
}

void UPowerUpSystem::ScoreTriggered(float Score)
{
	for (const auto powerUp : AppliedPowerUps)
	{
		powerUp->AddScore(Score);
	}
}

void UPowerUpSystem::AddPowerUp(TObjectPtr<UPowerUpPrimaryDataAsset> DataAsset)
{
	IPowerUp* PowerUp = Factory->CreatePowerup(DataAsset);
	TScriptInterface<IPowerUp> PowerUpInt;
	PowerUpInt.SetInterface(PowerUp);
	PowerUpInt.SetObject(Cast<UObject>(PowerUp));
	
	if(IIUpdatablePowerUp* UpdatablePowerUp = Cast<IIUpdatablePowerUp>(PowerUp); UpdatablePowerUp != nullptr)
	{
		TScriptInterface<IIUpdatablePowerUp> UpdatablePowerUpInt;
		UpdatablePowerUpInt.SetInterface(UpdatablePowerUp);
		UpdatablePowerUpInt.SetObject(Cast<UObject>(UpdatablePowerUp));
		
		UpdatablePowerUps.Add(UpdatablePowerUpInt);
	}
	AppliedPowerUps.Add(PowerUpInt);
}

void UPowerUpSystem::Tick(const float DeltaTime)
{
	for (const auto UpdatablePowerUp : UpdatablePowerUps)
	{
		UpdatablePowerUp->Update(DeltaTime);
	}
}