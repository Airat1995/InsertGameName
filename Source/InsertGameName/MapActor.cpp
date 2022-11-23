// Fill out your copyright notice in the Description page of Project Settings.


#include "MapActor.h"


// Sets default values
AMapActor::AMapActor()
{
}

void AMapActor::FillTargetPoints()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPlaceActor::StaticClass(), Actors);

	for (const auto Actor : Actors)
	{
		TargetPoints.Add(Cast<ATargetPlaceActor>(Actor));
	}
	bCached = true;
}
