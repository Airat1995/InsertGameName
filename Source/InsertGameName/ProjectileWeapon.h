#pragma once

#include "CoreMinimal.h"
#include "ProjectileWeaponDataAsset.h"
#include "Weapon.h"
#include "Projectile/ProjectileFactory.h"
#include "Projectile/ProjectilePool.h"
#include "ProjectileWeapon.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INSERTGAMENAME_API AProjectileWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	AProjectileWeapon();

	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

protected:

	virtual void Firing() override;

	virtual void AttachWeapon(const APlayerController* const Controller, UAnimInstance* const AnimInstance) override;

	UPROPERTY()
	UProjectileWeaponDataAsset* ProjectileWeaponDataAsset;


	ProjectileFactory* Factory;
	ProjectilePool* Pool;
};
