// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractWindowPresenter.h"

void UAbstractWindowPresenter::Open()
{
	WindowView->Open();
}

void UAbstractWindowPresenter::Close()
{
	WindowView->Close();
}

void UAbstractWindowPresenter::DestroyWindow()
{
}
