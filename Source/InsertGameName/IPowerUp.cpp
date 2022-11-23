// Fill out your copyright notice in the Description page of Project Settings.


#include "IPowerUp.h"


// Add default functionality here for any IIPowerUp functions that are not pure virtual.
void IPowerUp::AddScore(const float Score)
{
	if(Score >= ScoreToTrigger)
		TriggerCount -= 1;

	if(TriggerCount == 0)
	{
		Use();
		ResetTrigger();
	}
}

void IPowerUp::ResetTrigger()
{
	SetTriggeringCount(InitialTriggerCount);
}

void IPowerUp::SetTriggeringCount(const uint8 Count)
{
	TriggerCount = Count;
	InitialTriggerCount = Count;
}

void IPowerUp::SetScoreToTrigger(const float Score)
{
	ScoreToTrigger = Score;
}
