// Fill out your copyright notice in the Description page of Project Settings.


#include "MapAssetManager.h"

const FPrimaryAssetType	UMapAssetManager::MapAssetType = TEXT("Map");
const FPrimaryAssetType	UMapAssetManager::TargetAssetType = TEXT("Target");
const FPrimaryAssetType	UMapAssetManager::PowerUpAssetType = TEXT("PowerUp");
const FPrimaryAssetType	UMapAssetManager::TimerPowerUpAssetType = TEXT("TimerPowerUp");
const FPrimaryAssetType	UMapAssetManager::ScoreMultiplierPowerUpAssetType = TEXT("ScoreMultiplierPowerUp");
const FPrimaryAssetType UMapAssetManager::WindowAssetType = TEXT("Window");

UMapAssetManager& UMapAssetManager::Get()
{
	if (UAssetManager* Manager = GetIfValid())
	{
		UMapAssetManager* ThisAssetManager = Cast<UMapAssetManager>(Manager);
		return *ThisAssetManager;
	}
	UE_LOG(LogTemp, Fatal, TEXT("Failed to get AtreaAssetManager from DefaultEngine.ini"));
	return *NewObject<UMapAssetManager>();
}

TArray<TObjectPtr<UMapDataAsset>> UMapAssetManager::GetAllMaps() const
{
	TArray<FName> BundleNames;
	BundleNames.Add("Game");
	BundleNames.Add("Targets");
	TArray<FAssetData> Assets;
	GetPrimaryAssetDataList(MapAssetType, Assets);

	TArray<TObjectPtr<UMapDataAsset>> MapDataAssets;

	for (const auto MapAsset : Assets)
	{
		MapDataAssets.Add(Cast<UMapDataAsset>(MapAsset.GetAsset()));
	}
	
	return MapDataAssets;
}

void UMapAssetManager::LoadMapData(const FPrimaryAssetId& AssetId, FMapDataAssetLoaded& RequestedMapDataAssetLoaded)
{
	TArray<FName> BundlesToLoad;
	BundlesToLoad.Add(FName("Game"));
	BundlesToLoad.Add(FName("PowerUps"));
	BundlesToLoad.Add(FName("Targets"));
	MapDataAssetLoaded = MakeShared<FMapDataAssetLoaded>(RequestedMapDataAssetLoaded);
	MapDataLoadDelegate.BindUObject(this, &UMapAssetManager::MapLoaded, AssetId);
		
	MapStreamableHandle = LoadPrimaryAsset(AssetId, BundlesToLoad, MapDataLoadDelegate);
}

TArray<TObjectPtr<UWindowDataAsset>> UMapAssetManager::GetAllWindows() const
{
	TArray<FName> BundleNames;
	BundleNames.Add("Game");
	BundleNames.Add("Window");
	TArray<FAssetData> Assets;
	GetPrimaryAssetDataList(WindowAssetType, Assets);

	TArray<TObjectPtr<UWindowDataAsset>> WindowDataAssets;

	for (const auto WindowAsset : Assets)
	{
		WindowDataAssets.Add(Cast<UWindowDataAsset>(WindowAsset.GetAsset()));
	}
	
	return WindowDataAssets;
}

void UMapAssetManager::LoadWindowData(const FPrimaryAssetId& AssetId, FWindowAssetLoaded& WindowAssetLoaded)
{
	TArray<FName> BundleNames;
	BundleNames.Add("Game");
	BundleNames.Add("Window");
	
	WindowDataAssetsLoaded = MakeShared<FWindowAssetLoaded>(WindowAssetLoaded);
	WindowLoadDelegate.BindUObject(this, &UMapAssetManager::WindowLoaded, AssetId);
		
	WindowHandle = LoadPrimaryAsset(AssetId, BundleNames, MapDataLoadDelegate);
}

void UMapAssetManager::LoadTargetData(const FPrimaryAssetId& AssetId, FTargetDataAssetLoaded& RequestedMapDataAssetLoaded)
{
	TArray<FName> BundlesToLoad;
	BundlesToLoad.Add(FName("Targets"));
	TargetDataAssetLoaded = MakeShared<FTargetDataAssetLoaded>(RequestedMapDataAssetLoaded);
	TargetDataLoadDelegate.BindUObject(this, &UMapAssetManager::TargetLoaded, AssetId);
		
	TargetStreamableHandle = LoadPrimaryAsset(AssetId, BundlesToLoad, TargetDataLoadDelegate);
}

void UMapAssetManager::LoadPowerUpsData(const TArray<FPrimaryAssetId>& AssetIds,
	FPowerUpsAssetsLoaded& PowerUpsAssetsLoaded)
{
	TArray<FName> BundlesToLoad;
	BundlesToLoad.Add(FName("PowerUps"));
	PowerUpsDataAssetsLoaded = MakeShared<FPowerUpsAssetsLoaded>(PowerUpsAssetsLoaded);
	PowerUpLoadDelegate.BindUObject(this, &UMapAssetManager::PowerUpsLoaded, AssetIds);

	PowerUpHandle = LoadPrimaryAssets(AssetIds, BundlesToLoad, PowerUpLoadDelegate);
}

void UMapAssetManager::MapLoaded(FPrimaryAssetId AssetId)
{
	const UMapDataAsset* Asset = Cast<UMapDataAsset>(MapStreamableHandle->GetLoadedAsset());
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, Asset->GetLevelName().ToString());
	MapDataAssetLoaded->Execute(Asset);
	MapDataAssetLoaded.Reset();
	MapStreamableHandle.Reset();
	MapDataLoadDelegate.Unbind();
}

void UMapAssetManager::TargetLoaded(FPrimaryAssetId AssetId)
{
	const UTargetDataAsset* Asset = Cast<UTargetDataAsset>(TargetStreamableHandle->GetLoadedAsset());
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, FString::Printf(TEXT("Health: %f"), Asset->GetHealth()));
	TargetDataAssetLoaded->Execute(Asset);
	TargetDataAssetLoaded.Reset();
	TargetStreamableHandle.Reset();
	TargetDataLoadDelegate.Unbind();
}

void UMapAssetManager::PowerUpsLoaded(TArray<FPrimaryAssetId> AssetIds)
{
	TArray<UObject*> LoadedAssets;
	PowerUpHandle->GetLoadedAssets(LoadedAssets);
	TArray<UPowerUpPrimaryDataAsset*> DataAssets;
	for (const auto PowerUpAsset : LoadedAssets)
	{
		UPowerUpPrimaryDataAsset* Asset = Cast<UPowerUpPrimaryDataAsset>(PowerUpAsset);
		DataAssets.Add(Asset);
	}
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, FString::Printf(TEXT("Power Ups Loaded: %i"), DataAssets.Num()));
	PowerUpsDataAssetsLoaded->Execute(DataAssets);
	PowerUpsDataAssetsLoaded.Reset();
	PowerUpHandle.Reset();
	PowerUpLoadDelegate.Unbind();
}

void UMapAssetManager::WindowLoaded(FPrimaryAssetId PrimaryAssetId)
{
	const UWindowDataAsset* Asset = Cast<UWindowDataAsset>(WindowHandle->GetLoadedAsset());
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, Asset->GetWindowName().ToString());
	WindowDataAssetsLoaded->Execute(Asset);
	WindowDataAssetsLoaded.Reset();
	WindowHandle.Reset();
	TargetDataLoadDelegate.Unbind();
}
