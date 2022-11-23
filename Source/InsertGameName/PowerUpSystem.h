// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPowerUp.h"
#include "MultiplierPowerUp.h"
#include "PowerUpFactory.h"
#include "UObject/Object.h"
#include "PowerUpSystem.generated.h"

/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API UPowerUpSystem : public UObject
{
	GENERATED_BODY()

public:

	static UPowerUpSystem* Make(TObjectPtr<UObject> Parent, TObjectPtr<UGlobalTimer> Timer, TObjectPtr<UScoreCounter> ScoreCounter);

	virtual ~UPowerUpSystem() override;

	void ScoreTriggered(float Score);

	void AddPowerUp(TObjectPtr<UPowerUpPrimaryDataAsset> DataAsset);

	void Tick(const float DeltaTime);

private:

	UPROPERTY()
	UPowerUpFactory* Factory;

	UPROPERTY()
	TArray<TScriptInterface<IPowerUp>> AppliedPowerUps;

	UPROPERTY()
	TArray<TScriptInterface<IIUpdatablePowerUp>> UpdatablePowerUps;
};
