// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapDataAsset.h"
#include "WindowDataAsset.h"
#include "Engine/AssetManager.h"
#include "MapAssetManager.generated.h"

DECLARE_DELEGATE_OneParam(FMapDataAssetLoaded, const UMapDataAsset* const);
DECLARE_DELEGATE_OneParam(FTargetDataAssetLoaded, const UTargetDataAsset* const);
DECLARE_DELEGATE_OneParam(FPowerUpsAssetsLoaded, const TArray<UPowerUpPrimaryDataAsset*>);
DECLARE_DELEGATE_OneParam(FWindowAssetLoaded, const UWindowDataAsset* const);

/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API UMapAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:

	static const FPrimaryAssetType MapAssetType;
	static const FPrimaryAssetType TargetAssetType;
	static const FPrimaryAssetType PowerUpAssetType;
	static const FPrimaryAssetType TimerPowerUpAssetType;
	static const FPrimaryAssetType ScoreMultiplierPowerUpAssetType;
	static const FPrimaryAssetType WindowAssetType;
	

	static UMapAssetManager& Get();

	/** Map asset management region */
	TArray<TObjectPtr<UMapDataAsset>> GetAllMaps() const;
	void LoadMapData(const FPrimaryAssetId& AssetId, FMapDataAssetLoaded& RequestedMapDataAssetLoaded);

	TArray<TObjectPtr<UWindowDataAsset>> GetAllWindows() const;
	
	void LoadWindowData(const FPrimaryAssetId& AssetId, FWindowAssetLoaded& WindowAssetLoaded);

	/** Target asset management region */
	void LoadTargetData(const FPrimaryAssetId& AssetId, FTargetDataAssetLoaded& RequestedMapDataAssetLoaded);

	void LoadPowerUpsData(const TArray<FPrimaryAssetId>& AssetIds, FPowerUpsAssetsLoaded& PowerUpsAssetsLoaded);

private:

	TSharedPtr<FStreamableHandle> MapStreamableHandle;
	FStreamableDelegate MapDataLoadDelegate;
	TSharedPtr<FMapDataAssetLoaded> MapDataAssetLoaded;

	TSharedPtr<FStreamableHandle> TargetStreamableHandle;
	FStreamableDelegate TargetDataLoadDelegate;
	TSharedPtr<FTargetDataAssetLoaded> TargetDataAssetLoaded;

	TSharedPtr<FStreamableHandle> PowerUpHandle;
	FStreamableDelegate PowerUpLoadDelegate;
	TSharedPtr<FPowerUpsAssetsLoaded> PowerUpsDataAssetsLoaded;

	TSharedPtr<FStreamableHandle> WindowHandle;
	FStreamableDelegate WindowLoadDelegate;
	TSharedPtr<FWindowAssetLoaded> WindowDataAssetsLoaded;


	UFUNCTION()
	void MapLoaded(FPrimaryAssetId AssetId);

	UFUNCTION()
	void TargetLoaded(FPrimaryAssetId AssetId);

	UFUNCTION()
	void PowerUpsLoaded(TArray<FPrimaryAssetId> AssetIds);

	UFUNCTION()
	void WindowLoaded(FPrimaryAssetId PrimaryAssetId);
	
};