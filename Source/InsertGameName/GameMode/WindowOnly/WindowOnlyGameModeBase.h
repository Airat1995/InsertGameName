// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WindowOnlyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API AWindowOnlyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
};
