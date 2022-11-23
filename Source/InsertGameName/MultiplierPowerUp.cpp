// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplierPowerUp.h"

UMultiplierPowerUp* UMultiplierPowerUp::Make(UObject* Parent, const TObjectPtr<UScoreCounter> Counter, const TObjectPtr<UScoreMultPowerUpPrimaryDataAsset> DataAsset)
{
	UMultiplierPowerUp* MultiplierPowerUp = NewObject<UMultiplierPowerUp>(Parent);
	MultiplierPowerUp->SetTriggeringCount(DataAsset->GetTriggerCountBeforeActivation());
	MultiplierPowerUp->SetScoreToTrigger(DataAsset->GetScoreToTrigger());
	MultiplierPowerUp->SetActiveTime(DataAsset->GetActiveTime());
	MultiplierPowerUp->MultiplyCount = DataAsset->GetScoreMultiplier();
	MultiplierPowerUp->ScoreCounter = Counter;
	MultiplierPowerUp->SubscribeOnStartPowerUp(MultiplierPowerUp, &UMultiplierPowerUp::StartScoreMultiply);
	MultiplierPowerUp->SubscribeOnEndPowerUp(MultiplierPowerUp, &UMultiplierPowerUp::EndScoreMultiply);

	return MultiplierPowerUp;
}

void UMultiplierPowerUp::AddScore(float Score)
{
	IIUpdatablePowerUp::AddScore(Score);

	if(GetIsActive())
		ScoreCounter->AddScore((MultiplyCount - 1) * Score);
}

void UMultiplierPowerUp::StartScoreMultiply()
{
	ScoreCounter->SetScoreMultiplier(MultiplyCount);
}

void UMultiplierPowerUp::EndScoreMultiply()
{
	ScoreCounter->SetScoreMultiplier(1);
}
