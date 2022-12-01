// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Service.h"
#include "Base/BaseUI.h"
#include "InsertGameName/InsertGameName.h"
#include "Interface/AbstractWindowController.h"
#include "Interface/WindowFactory.h"

/**
 * 
 */
class INSERTGAMENAME_API AbstractWindowService : public IService
{
public:
	AbstractWindowService(): BaseUI()
	{
	}

	virtual ~AbstractWindowService() override
	{
		
	}
	
	void RegisterWindowFactory(IWindowFactory* WindowFactory)
	{
		WindowFactories.Add(WindowFactory->GetWindowControllerType(), WindowFactory);
	}

	void OpenWindow(const UClass* WindowController)
	{
		if(ClosedWindows.Contains(WindowController))
		{
			UAbstractWindowController* Window = ClosedWindows[WindowController];
			Window->Open();

		}
		//Before creating a new window instance we should check if it wasn't open previously
		else if(OpenedWindows.Contains(WindowController))
		{
			UE_LOG(WindowManager, Error, TEXT("Trying to open window that already opened"));
		}
		else if(WindowFactories.Contains(WindowController))
		{
			IWindowFactory* WindowFactory = WindowFactories[WindowController];
			UAbstractWindowController* Window = WindowFactory->CreateWindow();
			Window->Open();
			OpenedWindows.Add( WindowController, Window);
		}
	}

	void CloseWindow(const UClass* WindowController)
	{
		if(OpenedWindows.Contains(WindowController))
		{
			UAbstractWindowController* FoundWindow = OpenedWindows[WindowController];
			OpenedWindows.Remove(WindowController);
			FoundWindow->Close();
			ClosedWindows.Add(WindowController, FoundWindow);
		}
	}

	void DestroyWindow(const UClass* WindowController)
	{
		if(ClosedWindows.Contains(WindowController))
		{
			UAbstractWindowController* FoundWindow = ClosedWindows[WindowController];
			ClosedWindows.Remove(WindowController);
			FoundWindow->DestroyWindow();
		}
		else if(OpenedWindows.Contains(WindowController))
		{
			UE_LOG(WindowManager, Error, TEXT("Trying to destroy open window!"));
		}
	}

private:
	
	TMap<const UClass*, UAbstractWindowController*> OpenedWindows;
	TMap<const UClass*, UAbstractWindowController*> ClosedWindows;
	TMap<const UClass*, IWindowFactory*> WindowFactories;
	TObjectPtr<UBaseUI> BaseUI;
	
};

// Used for IOC registrations
Expose_TNameOf(AbstractWindowService)
