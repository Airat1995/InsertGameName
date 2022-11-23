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
	AbstractWindowService();
	virtual ~AbstractWindowService() override;
	
	
	void RegisterWindowFactory(IWindowFactory* WindowFactory)
	{
		WindowFactories.Add(WindowFactory->GetWindowControllerType(), WindowFactory);
	}

	void OpenWindow(UClass* WindowController)
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
			OpenedWindows.Add( WindowController, Window);
		}
	}

	template<typename WindowType,
			std::enable_if_t<std::is_base_of_v<UAbstractWindowController, WindowType>>>
	void CloseWindow()
	{
		if(OpenedWindows.Contains(WindowType::StaticClass))
		{
			UAbstractWindowController* FoundWindow = OpenedWindows.Find(WindowType::StaticClass);
			OpenedWindows.Remove(WindowType::StaticClass);
			FoundWindow->Close();
			ClosedWindows.Add(WindowType::StaticClass, FoundWindow);
		}
	}

	template<typename WindowType,
		std::enable_if_t<std::is_base_of_v<UAbstractWindowController, WindowType>>>
	void DestroyWindow()
	{
		if(ClosedWindows.Contains(WindowType::StaticClass))
		{
			UAbstractWindowController* FoundWindow = ClosedWindows.Find(WindowType::StaticClass);
			ClosedWindows.Remove(WindowType::StatiClass);
			FoundWindow->DestroyWindow();
		}
		else if(OpenedWindows.Contains(WindowType::StaticClass))
		{
			UE_LOG(WindowManager, Error, TEXT("Trying to destroy open window!"));
		}
	}

private:
	
	TMap<UClass*, UAbstractWindowController*> OpenedWindows;
	TMap<UClass*, UAbstractWindowController*> ClosedWindows;
	TMap<UClass*, IWindowFactory*> WindowFactories;
	UBaseUI* BaseUI;
	
};

// Used for IOC registrations
Expose_TNameOf(AbstractWindowService)
