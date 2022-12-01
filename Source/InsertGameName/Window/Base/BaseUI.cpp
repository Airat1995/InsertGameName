// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseUI.h"

void UBaseUI::OpenWindow(TObjectPtr<UAbstractWindowController> WindowController) const
{
	WindowStack->AddWidgetInstance(*WindowController->GetWindowView());
}

void UBaseUI::CloseWindow(TObjectPtr<UAbstractWindowController> WindowController) const
{
	WindowStack->RemoveWidget(*WindowController->GetWindowView());
}
