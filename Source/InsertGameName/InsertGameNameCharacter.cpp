// Copyright Epic Games, Inc. All Rights Reserved.

#include "InsertGameNameCharacter.h"
#include "Character/PBPlayerMovement.h"


//////////////////////////////////////////////////////////////////////////
// AInsertGameNameCharacter

AInsertGameNameCharacter::AInsertGameNameCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	TurnRateGamepad = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	WeaponCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("WeaponCollision"));
	WeaponCollisionComponent->SetupAttachment(Mesh1P);
}

void AInsertGameNameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	WeaponCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AInsertGameNameCharacter::WeaponOverlay);
}

void AInsertGameNameCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();
	ArsenalComponent = UArsenalComponent::Make(this, Cast<APlayerController>(GetController()), Mesh1P->GetAnimInstance());

}

void AInsertGameNameCharacter::WeaponOverlay(UPrimitiveComponent* OvelapComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComponent, int iOtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	if(OtherActor->IsA<AWeapon>())
	{
		AWeapon* Weapon = Cast<AWeapon>(OtherActor);
		AttachWeapon(Weapon);
	}
}

void AInsertGameNameCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AInsertGameNameCharacter::OnPrimaryActionStart() const
{
	ArsenalComponent->StartFiring();
}

void AInsertGameNameCharacter::OnPrimaryActionEnd() const
{
	ArsenalComponent->StopFiring();
}

void AInsertGameNameCharacter::SwitchNextWeapon() const
{
	ArsenalComponent->WearNextWeapon();
}

void AInsertGameNameCharacter::SwitchPreviousWeapon() const
{
	ArsenalComponent->WearPreviousWeapon();
}

void AInsertGameNameCharacter::Crouching() const
{
	Cast<UPBPlayerMovement>(GetMovementComponent())->Crouch (true);
}

void AInsertGameNameCharacter::UnCrouching() const
{
	Cast<UPBPlayerMovement>(GetMovementComponent())->UnCrouch(true);
}

void AInsertGameNameCharacter::StartSprint()
{
	SetSprinting(true);
}

void AInsertGameNameCharacter::StopSprint()
{
	SetSprinting(false);
}

void AInsertGameNameCharacter::MoveForward(float Value)
{
	if (!FMath::IsNearlyZero(Value))
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AInsertGameNameCharacter::MoveRight(float Value)
{
	if (!FMath::IsNearlyZero(Value))
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AInsertGameNameCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AInsertGameNameCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AInsertGameNameCharacter::AttachWeapon(AWeapon* Weapon)
{
	if(Weapon->IsAlreadyAttached())
		return;
	ArsenalComponent->AttachNewWeapon(Weapon);

	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	Weapon->AttachToComponent(GetMesh1P(),AttachmentRules, FName(TEXT("GripPoint")));

}
