// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include  "GlobalTimer.generated.h"
DECLARE_DELEGATE(FOnTimerEnd);


/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API UGlobalTimer : public UObject
{
	GENERATED_BODY()
public:

	static UGlobalTimer* Make(const TObjectPtr<UObject> Parent);
	
	UGlobalTimer();
	virtual ~UGlobalTimer() override;

	void SetTimer(float timer);
	void AddTime(float time);
	void Reset();
	void Start();
	void Tick(float deltaTime);

	template< class UserClass >
	void SubscribeOnTimerEnd(UserClass* Object, typename FInputActionHandlerSignature::TMethodPtr< UserClass > Func )
	{
		TimerEnd.BindUObject(Object, Func);
	}

private:
	FOnTimerEnd TimerEnd;
	float CurrentTimeLeft;
	float InitialTime;
	bool bTimerStarted;
};
