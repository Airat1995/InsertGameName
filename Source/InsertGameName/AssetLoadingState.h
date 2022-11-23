// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetLoadingState.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAssetLoadingState : uint8
{
	NotLoading,
	Loading,
	Loaded
};
