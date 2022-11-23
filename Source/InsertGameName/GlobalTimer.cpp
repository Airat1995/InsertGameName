// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalTimer.h"


UGlobalTimer* UGlobalTimer::Make(const TObjectPtr<UObject> Parent)
{
	UGlobalTimer* Timer = NewObject<UGlobalTimer>(Parent);

	return Timer;
}

UGlobalTimer::UGlobalTimer()
{
}

UGlobalTimer::~UGlobalTimer()
{
	TimerEnd.Unbind();
}

void UGlobalTimer::SetTimer(float timer)
{
	check(timer > 0);
	InitialTime = timer;
	CurrentTimeLeft = timer;
	bTimerStarted = false;
}

void UGlobalTimer::AddTime(float time)
{
	CurrentTimeLeft += time;
}

void UGlobalTimer::Reset()
{
	SetTimer(InitialTime);
}

void UGlobalTimer::Start()
{
	bTimerStarted = true;
}

void UGlobalTimer::Tick(float deltaTime)
{
	if(!bTimerStarted)
		return;
	CurrentTimeLeft -= deltaTime;
	if(CurrentTimeLeft <= 0)
	{
		TimerEnd.ExecuteIfBound();
		bTimerStarted = false;
	}
}
