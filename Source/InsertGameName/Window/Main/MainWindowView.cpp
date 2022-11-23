// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWindowView.h"

void UMainWindowView::Open()
{
	AddToViewport();
	ActivateWidget();
}

void UMainWindowView::Close()
{
	DeactivateWidget();
	RemoveFromViewport();
}

void UMainWindowView::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMainWindowView::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMainWindowView::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
