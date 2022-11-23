// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WeaponDataAsset.h"
#include "EWeaponState.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon.generated.h"


UCLASS(Blueprintable, Abstract, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INSERTGAMENAME_API AWeapon : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
	UWeaponDataAsset* WeaponDataAsset;

	/** Sets default values for this component's properties */
	AWeapon();

	virtual void AttachWeapon(const APlayerController* const Controller, UAnimInstance* const AnimInstance);
	
	/** Make the weapon starts firing a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void FireStop();

	FORCEINLINE void Wear(bool wearing)
	{
		State = wearing ? EWeaponState::Idle : EWeaponState::NotWeared;
		SetActorHiddenInGame(!wearing);
		SetActorEnableCollision(!wearing);
	}

	FORCEINLINE bool IsReloading() const
	{
		return State == EWeaponState::Reloading;
	}

	FORCEINLINE bool IsAlreadyAttached() const
	{
		return State != EWeaponState::Detached;
	}


protected:
	// /** Ends gameplay for this component. */
	// UFUNCTION()
	// virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	

	virtual void Firing();

	uint8 iCurrentMagazineSize;
	EWeaponState State;
	UWorld* CurrentWorld;
	FDateTime _lastShootTime;
	FDateTime _startReloadingTime;
	const APlayerController* PlayerController;
	UAnimInstance* Anim;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual", meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = true))
	USphereComponent* PickupCollision;
};
