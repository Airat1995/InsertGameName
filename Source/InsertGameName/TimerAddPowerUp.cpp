// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerAddPowerUp.h"


UTimerAddPowerUp* UTimerAddPowerUp::Make(TObjectPtr<UObject> Parent, const TObjectPtr<UGlobalTimer> Timer, const TObjectPtr<UTimerPowerUpPrimaryDataAsset> DataAsset)
{
	UTimerAddPowerUp* TimerAddPowerUp = NewObject<UTimerAddPowerUp>(Parent);
	TimerAddPowerUp->Timer = Timer;
	TimerAddPowerUp->TimeToAdd = DataAsset->GetTimerAdd();
	TimerAddPowerUp->SetTriggeringCount(DataAsset->GetTriggerCountBeforeActivation());
	TimerAddPowerUp->SetScoreToTrigger(DataAsset->GetScoreToTrigger());

	return TimerAddPowerUp;
}

void UTimerAddPowerUp::Use()
{
	Timer->AddTime(TimeToAdd);
}