// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapDifficultyZones.h"
#include "UObject/Object.h"
#include "ScoreCounter.generated.h"

/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API UScoreCounter : public UObject
{
	GENERATED_BODY()

public:

	static TObjectPtr<UScoreCounter> Make(const TObjectPtr<UObject> Parent);
	void SetDifficulty(FMapDifficultyZones MapDifficultyZones);

	void AddScore(float Score);

	float GetFinalScore() const;
	void SetScoreMultiplier(float MultiplyCount);

private:

	float Score;
	float Multiplier;
	FMapDifficultyZones DifficultyZones;
};
