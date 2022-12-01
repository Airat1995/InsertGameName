// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Interface/AbstractWindowController.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "BaseUI.generated.h"

/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API UBaseUI : public UCommonActivatableWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = true))
	UCommonActivatableWidgetStack* WindowStack;

public:

	void OpenWindow(TObjectPtr<UAbstractWindowController> WindowController) const;

	void CloseWindow(TObjectPtr<UAbstractWindowController> WindowController) const;
};
