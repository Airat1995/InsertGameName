// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetPlaceActor.h"

#include "Target.h"

// Sets default values
ATargetPlaceActor::ATargetPlaceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

FTransform ATargetPlaceActor::GetSpawnTargetPosition()
{
	const int spawnObjectPosition = FMath::RandRange(0, SpawnTransforms.Num() - 1);
	const FTransform SpawnTransform = GetTransform() + SpawnTransforms[spawnObjectPosition];

	return SpawnTransform;
}