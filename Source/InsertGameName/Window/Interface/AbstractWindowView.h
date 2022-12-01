// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "AbstractWindowView.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class INSERTGAMENAME_API UAbstractWindowView : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	virtual void Open() PURE_VIRTUAL(UAbstractWindowView::Open,);

	virtual void Close() PURE_VIRTUAL(UAbstractWindowView::Close,);

	virtual void DestroyWindow() PURE_VIRTUAL(UAbstractWindowView::DestroyWindow,);
};
