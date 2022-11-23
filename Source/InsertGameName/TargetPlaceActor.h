// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetPlaceActor.generated.h"

UCLASS()
class INSERTGAMENAME_API ATargetPlaceActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetPlaceActor();
	
	UFUNCTION(BlueprintCallable)
	FTransform GetSpawnTargetPosition();

private:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = true))
	TArray<FTransform> SpawnTransforms;
	
};
