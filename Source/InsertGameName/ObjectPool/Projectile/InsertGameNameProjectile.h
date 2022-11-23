// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "MainWeaponProjectileDataAsset.h"
#include "PoolObject.h"
#include "../Target.h"
#include "InsertGameNameProjectile.generated.h"

class UMainWeaponProjectileDataAsset;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class AInsertGameNameProjectile : public AActor, public UPoolObject
{
	GENERATED_BODY()
public:
	AInsertGameNameProjectile();
	
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	UMainWeaponProjectileDataAsset* WeaponDataAsset;

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	virtual void InternalDestroy() override;

	void SetVelocity() const;

	void SetMove(bool bShouldMove) const;
};


