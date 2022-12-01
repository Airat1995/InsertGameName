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
	
	virtual void Open() PURE_VIRTUAL(UAbstractWindowController::Open,);

	virtual void Close() PURE_VIRTUAL(UAbstractWindowController::Close,);

	virtual void DestroyWindow() PURE_VIRTUAL(UAbstractWindowController::DestroyWindow,);
	
	FORCEINLINE TObjectPtr<UCommonActivatableWidget> GetWindowView() const PURE_VIRTUAL(UAbstractWindowController::GetWindowView, return nullptr; );
};
