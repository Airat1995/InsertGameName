// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPowerUp.h"
#include "IUpdatablePowerUp.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnStartPowerUp)
DECLARE_MULTICAST_DELEGATE(FOnEndPowerUp)

// This class does not need to be modified.
UINTERFACE()
class UIUpdatablePowerUp : public UPowerUp
{
	GENERATED_BODY()
};

/**
 * 
 */
class INSERTGAMENAME_API IIUpdatablePowerUp : public IPowerUp
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	template<class UserClass>
	void SubscribeOnStartPowerUp(UserClass* Object, typename TBaseDynamicDelegate<FWeakObjectPtr, void>::template TMethodPtrResolver<UserClass>::FMethodPtr Func)
	{
		OnStartPowerUp.AddUObject(Object, Func);
	}

	template<class  UserClass>
	void SubscribeOnEndPowerUp(UserClass* Object, typename TBaseDynamicDelegate<FWeakObjectPtr, void>::template TMethodPtrResolver<UserClass>::FMethodPtr Func)
	{
		OnEndPowerUp.AddUObject(Object, Func);
	}

	virtual void AddScore(float Score) override;
	virtual void Update(float DeltaTime);
	virtual void Use() override;

protected:

	void SetActiveTime(float Time);
	FORCEINLINE bool GetIsActive()
	{
		return bIsActive;
	}

private:
	/** How long after activation power up stays active */
	float ActiveTime = 0;
	FOnStartPowerUp OnStartPowerUp;
	FOnEndPowerUp OnEndPowerUp;
	bool bIsActive = false;
};
