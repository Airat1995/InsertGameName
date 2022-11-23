// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/InsertGameNameProjectile.h"
#include "WeaponDataAsset.h"
#include "ProjectileWeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class INSERTGAMENAME_API UProjectileWeaponDataAsset : public UWeaponDataAsset
{
	GENERATED_BODY()

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile, meta = (AllowPrivateAccess = true))
	TSubclassOf<AInsertGameNameProjectile> ProjectileClass;

public:

	FORCEINLINE TSubclassOf<AInsertGameNameProjectile> GetProjectileClass() const noexcept
	{
		return ProjectileClass;
	}
};
