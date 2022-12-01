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
	virtual void Open() PURE_VIRTUAL(UAbstractWindowPresenter::Open,);

	virtual void Close() PURE_VIRTUAL(UAbstractWindowPresenter::Close,);

	virtual void DestroyWindow() PURE_VIRTUAL(UAbstractWindowPresenter::DestroyWindow,);
	
	virtual TObjectPtr<UCommonActivatableWidget> GetView() const  PURE_VIRTUAL(UAbstractWindowPresenter::GetView, return nullptr; );
};
