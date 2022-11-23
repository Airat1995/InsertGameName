// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PowerUpPrimaryDataAsset.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class UPowerUpPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset", meta = (AllowPrivateAccess = true))
	FPrimaryAssetType Type;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base", meta = (AllowPrivateAccess = true))
	float ScoreToTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base", meta = (AllowPrivateAccess = true))
	uint8 TriggerBeforeActivate;

public:

	FORCEINLINE float GetScoreToTrigger() const noexcept
	{
		return ScoreToTrigger;
	}

	FORCEINLINE uint8 GetTriggerCountBeforeActivation() const noexcept
	{
		return TriggerBeforeActivate;
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
