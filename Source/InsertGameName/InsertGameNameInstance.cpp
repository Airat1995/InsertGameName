// Fill out your copyright notice in the Description page of Project Settings.


#include "InsertGameNameInstance.h"

#include "AbstractWindowService.h"
#include "MainWindowService.h"

UInsertGameNameInstance::UInsertGameNameInstance()
{
}

void UInsertGameNameInstance::SetMapDataAsset(TObjectPtr<UMapDataAsset> DataAsset)
{
	MapDataAsset = DataAsset;
}

TObjectPtr<UMapDataAsset> UInsertGameNameInstance::GetMapDataAsset() const noexcept
{
	const UMapAssetManager& AssetManager = UMapAssetManager::Get();

	TArray<TObjectPtr<UMapDataAsset>> Assets = AssetManager.GetAllMaps();

	return Assets[0];

}

void UInsertGameNameInstance::SetSelectedDifficulty(EDifficulty Difficulty) noexcept
{
	SelectedDifficulty = Difficulty;
}

EDifficulty UInsertGameNameInstance::GetSelectedDifficulty() const noexcept
{
	return SelectedDifficulty;
}

TObjectPtr<UServiceContainer> UInsertGameNameInstance::GetServiceContainer() const noexcept
{
	return ServiceContainer;
}

void UInsertGameNameInstance::OnStart()
{
	Super::OnStart();
	
	ServiceContainer = NewObject<UServiceContainer>();
	ServiceContainer->RegisterService<AbstractWindowService, UMainWindowService>();
}