// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeapon.h"
#include "InsertGameNameCharacter.h"


// Sets default values for this component's properties
AProjectileWeapon::AProjectileWeapon()
{
	SetActorTickEnabled(false);
}

void AProjectileWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileWeapon::BeginDestroy()
{
	Super::BeginDestroy();
	delete Pool;
	delete Factory;
}

void AProjectileWeapon::Firing()
{
	Super::Firing();
	const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	const FVector SpawnPosition = MeshComponent->GetSocketLocation(WeaponDataAsset->MuzzleSocket);
	
	//Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AInsertGameNameProjectile* Projectile = Pool->GetObjectInstance();
	Projectile->SetActorLocation(SpawnPosition);
	Projectile->SetActorRotation(SpawnRotation);
	Projectile->SetVelocity();
}

void AProjectileWeapon::AttachWeapon(const APlayerController* const Controller, UAnimInstance* const AnimInstance)
{
	Super::AttachWeapon(Controller, AnimInstance);
	ProjectileWeaponDataAsset = Cast<UProjectileWeaponDataAsset>(WeaponDataAsset);
	Factory = new ProjectileFactory(GetWorld(), ProjectileWeaponDataAsset->GetProjectileClass());
	Pool = new ProjectilePool(*Factory);
}
