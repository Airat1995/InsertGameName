// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EDifficulty.h"
#include "../Target.h"
#include "Engine/DataAsset.h"

#include "TargetDataAsset.generated.h"


/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API UTargetDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset", meta = (AllowPrivateAccess = true))
	FPrimaryAssetType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay", meta = (AllowPrivateAccess = true))
	TMap<EDifficulty, FMapDifficultyZones> Zones;

	UPROPERTY(EditAnywhere, Category = "Gameplay", meta=(UIMin="0.0", UIMax="10000.0", AllowPrivateAccess = true))
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay", meta = (AllowPrivateAccess = true))
	TSubclassOf<ATarget> TargetType;

public:

	FORCEINLINE TSubclassOf<ATarget> GetTargetType() const noexcept
	{
		return TargetType;
	}

	FORCEINLINE const TMap<EDifficulty, FMapDifficultyZones>& GetZones() const noexcept
	{
		return Zones;
	}

	FORCEINLINE float GetHealth() const noexcept
	{
		return Health;
	}
	
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(Type, GetFName());
	}

	FString GetIdentifierString() const
	{
		return GetPrimaryAssetId().ToString();
	}
};
