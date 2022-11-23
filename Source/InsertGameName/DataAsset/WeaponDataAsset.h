// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "WeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class INSERTGAMENAME_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Gameplay)
	FName MuzzleSocket;

	/** How long player will wait, in seconds, before gun can shoot again with pressed mouse button */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Gameplay)
	float FireRate;

	/** How many bullets player can shoot before gun require reloading */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Gameplay)
	uint8 MagazineSize;

	/** How much time, in seconds, required to reload the weapon */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Gameplay)
	float ReloadTime;
	
	/** Gun's mesh */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Visual)
	USkeletalMesh* Mesh;
};
