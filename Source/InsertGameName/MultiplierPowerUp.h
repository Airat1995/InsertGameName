// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IUpdatablePowerUp.h"
#include "ScoreCounter.h"
#include "ScoreMultPowerUpPrimaryDataAsset.h"
#include "UObject/Object.h"
#include "MultiplierPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API UMultiplierPowerUp : public UObject, public IIUpdatablePowerUp
{
	GENERATED_BODY()

public:
	static UMultiplierPowerUp* Make(UObject* Parent, TObjectPtr<UScoreCounter> Counter, TObjectPtr<UScoreMultPowerUpPrimaryDataAsset> DataAsset);

	virtual void AddScore(float Score) override;
	
private:

	UFUNCTION()
	void StartScoreMultiply();

	UFUNCTION()
	void EndScoreMultiply();

	UPROPERTY()
	TObjectPtr<UScoreCounter> ScoreCounter;
	float MultiplyCount;
};

