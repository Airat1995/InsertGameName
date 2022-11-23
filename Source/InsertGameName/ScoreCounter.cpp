// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreCounter.h"

TObjectPtr<UScoreCounter> UScoreCounter::Make(const TObjectPtr<UObject> Parent)
{
	const TObjectPtr<UScoreCounter> ScoreCounter = NewObject<UScoreCounter>(Parent);
	ScoreCounter->Score = 0;
	return ScoreCounter;
}

void UScoreCounter::SetDifficulty(FMapDifficultyZones MapDifficultyZones)
{
	DifficultyZones = MapDifficultyZones;
}


void UScoreCounter::AddScore(float score)
{
	Score += score * Multiplier;
}

float UScoreCounter::GetFinalScore() const
{
	return Score * DifficultyZones.DifficultyScoreMultiplier;
}

void UScoreCounter::SetScoreMultiplier(float MultiplyCount)
{
	Multiplier = MultiplyCount;
}
