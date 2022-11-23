// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseUI.h"

void UBaseUI::OpenWindow(const UAbstractWindowController& WindowController) const
{
	WindowStack->AddWidgetInstance(WindowController.GetWindowView());
}

void UBaseUI::CloseWindow(const UAbstractWindowController& WindowController) const
{
	WindowStack->RemoveWidget(WindowController.GetWindowView());
}
