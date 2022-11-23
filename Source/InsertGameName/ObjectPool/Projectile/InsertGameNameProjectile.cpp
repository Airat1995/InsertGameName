// Copyright Epic Games, Inc. All Rights Reserved.

#include "InsertGameNameProjectile.h"


AInsertGameNameProjectile::AInsertGameNameProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));

	CollisionComp->OnComponentHit.AddDynamic(this, &AInsertGameNameProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
}


void AInsertGameNameProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != nullptr && OtherComp != nullptr && OtherActor->IsA<ATarget>())
	{
		ATarget* target = Cast<ATarget>(OtherActor);
		target->Damage(WeaponDataAsset->GetDamage(), Hit.Location);
	}
	ReturnToPool();
}

void AInsertGameNameProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AInsertGameNameProjectile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if(WeaponDataAsset != nullptr)
	{
		ProjectileMovement->InitialSpeed = WeaponDataAsset->GetSpeed();
		ProjectileMovement->MaxSpeed = WeaponDataAsset->GetSpeed();
		ProjectileMovement->bRotationFollowsVelocity = true;
		ProjectileMovement->bShouldBounce = false;
	}
}

void AInsertGameNameProjectile::InternalDestroy()
{
	Destroy();
}

void AInsertGameNameProjectile::SetVelocity() const
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector(WeaponDataAsset->GetSpeed(), 0,0 ));
}

void AInsertGameNameProjectile::SetMove(bool bShouldMove) const
{
	ProjectileMovement->SetActive(bShouldMove, true);
	ProjectileMovement->InitialSpeed = WeaponDataAsset->GetSpeed();
	ProjectileMovement->MaxSpeed = WeaponDataAsset->GetSpeed();
	if(!bShouldMove)
		ProjectileMovement->SetVelocityInLocalSpace(FVector(0, 0,0 ));
}
