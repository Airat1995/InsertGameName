// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/AbstractWindowView.h"
#include "MainWindowView.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class INSERTGAMENAME_API UMainWindowView : public UAbstractWindowView
{
	GENERATED_BODY()

public:
	virtual void Open() override;

	virtual void Close() override;

protected:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
