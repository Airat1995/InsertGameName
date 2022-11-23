// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractWindowView.h"
#include "UObject/Object.h"
#include "AbstractWindowPresenter.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class INSERTGAMENAME_API UAbstractWindowPresenter : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void Open();

	virtual void Close();

	virtual void DestroyWindow();
	
	FORCEINLINE UCommonActivatableWidget& GetView() const
	{
		return *WindowView;
	}

protected:

	UPROPERTY()
	UAbstractWindowView* WindowView;
};
