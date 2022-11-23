// Copyright Epic Games, Inc. All Rights Reserved.


#include "Weapon.h"


// Sets default values for this component's properties
AWeapon::AWeapon()
{
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;

	PickupCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Pickup Collision"));
	PickupCollision->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
	_lastShootTime = FDateTime::MinValue();
	State = EWeaponState::Detached;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponDataAsset != nullptr && WeaponDataAsset->FireSound != nullptr && WeaponDataAsset->FireAnimation != nullptr);
}

void AWeapon::Fire()
{
	if(State != EWeaponState::Idle)
		return;
	State = EWeaponState::Firing;
	CurrentWorld = GetWorld();
	SetActorTickEnabled(true);
}

void AWeapon::FireStop()
{
	if(IsReloading())
		return;
	State = EWeaponState::Idle;
	//Not deleting because we just cached those pointers we are not owners
	CurrentWorld = nullptr;
	SetActorTickEnabled(false);
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(State == EWeaponState::Reloading && (FDateTime::Now() - _startReloadingTime).GetTotalSeconds() < WeaponDataAsset->ReloadTime)
		return;
	if(State == EWeaponState::Reloading)
		State = EWeaponState::Idle;
	if(State != EWeaponState::Firing || (FDateTime::Now() - _lastShootTime).GetTotalSeconds() < WeaponDataAsset->FireRate)
		return;
	Firing();
	
	if(iCurrentMagazineSize <= 0)
	{
		_startReloadingTime = FDateTime::Now();
		iCurrentMagazineSize = WeaponDataAsset->MagazineSize;
		State = EWeaponState::Reloading;
	}
}

void AWeapon::Firing()
{
	State = EWeaponState::Firing;
	UGameplayStatics::PlaySoundAtLocation(this, WeaponDataAsset->FireSound, GetActorLocation());
	// Get the animation object for the arms mesh
	Anim->Montage_Play(WeaponDataAsset->FireAnimation, 1.f);
	_lastShootTime = FDateTime::Now();
	iCurrentMagazineSize -= 1;
}

void AWeapon::AttachWeapon(const APlayerController* const Controller, UAnimInstance* const AnimInstance)
{
	PlayerController = Controller;
	Anim = AnimInstance;
	State = EWeaponState::Idle;
	iCurrentMagazineSize = WeaponDataAsset->MagazineSize;
}

