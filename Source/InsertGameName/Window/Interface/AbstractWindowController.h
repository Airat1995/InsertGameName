// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractWindowPresenter.h"
#include "UObject/Object.h"
#include "AbstractWindowController.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class INSERTGAMENAME_API UAbstractWindowController : public UObject
{
	GENERATED_BODY()
	
public:
	
	virtual void Open();

	virtual void Close();

	virtual void DestroyWindow();
	
	FORCEINLINE UCommonActivatableWidget& GetWindowView() const
	{
		return WindowPresenter->GetView();
	}
	
protected:

	TObjectPtr<UAbstractWindowPresenter> WindowPresenter;
};
