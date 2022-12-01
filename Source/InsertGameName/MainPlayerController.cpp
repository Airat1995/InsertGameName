// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "GameMode/Gameplay/InsertGameNameGameMode.h"

AMainPlayerController::AMainPlayerController()
{

}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
		// Bind jump events
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMainPlayerController::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMainPlayerController::StopJumping);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &AMainPlayerController::Crouching);
	InputComponent->BindAction("Crouch", IE_Released, this, &AMainPlayerController::UnCrouching);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AMainPlayerController::StartSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AMainPlayerController::StopSprint);

	// Bind fire event
	InputComponent->BindAction("Use", IE_Pressed, this, &AMainPlayerController::StartPlay);
	InputComponent->BindAction("PrimaryAction", IE_Pressed, this, &AMainPlayerController::OnPrimaryActionStart);
	InputComponent->BindAction("PrimaryAction", IE_Released, this, &AMainPlayerController::OnPrimaryActionEnd);
	InputComponent->BindAction("Switch Weapon Next", IE_Pressed, this, &AMainPlayerController::SwitchNextWeapon);
	InputComponent->BindAction("Switch Weapon Previous", IE_Pressed, this, &AMainPlayerController::SwitchPreviousWeapon);

	// Enable touchscreen input
	EnableTouchscreenMovement();

	// Bind movement events
	InputComponent->BindAxis("Move Forward / Backward", this, &AMainPlayerController::MoveForward);
	InputComponent->BindAxis("Move Right / Left", this, &AMainPlayerController::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "Mouse" versions handle devices that provide an absolute delta, such as a mouse.
	// "Gamepad" versions are for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn Right / Left Mouse", this, &AMainPlayerController::AddControllerYawInput);
	InputComponent->BindAxis("Look Up / Down Mouse", this, &AMainPlayerController::AddControllerPitchInput);
	InputComponent->BindAxis("Turn Right / Left Gamepad", this, &AMainPlayerController::TurnAtRate);
	InputComponent->BindAxis("Look Up / Down Gamepad", this, &AMainPlayerController::LookUpAtRate);
}

void AMainPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PlayerCharacter = Cast<AInsertGameNameCharacter>(GetCharacter());
	InsertGameNameGameMode = Cast<AInsertGameNameGameMode>(GetWorld()->GetAuthGameMode());
}

void AMainPlayerController::Jump()
{
	PlayerCharacter->Jump();
}

void AMainPlayerController::StopJumping()
{
	PlayerCharacter->StopJumping();
}

void AMainPlayerController::Crouching()
{
	PlayerCharacter->Crouching();
}

void AMainPlayerController::UnCrouching()
{
	PlayerCharacter->UnCrouching();
}

void AMainPlayerController::StartSprint()
{
	PlayerCharacter->StartSprint();
}

void AMainPlayerController::StopSprint()
{
	PlayerCharacter->StopSprint();
}

void AMainPlayerController::StartPlay()
{
	if(InsertGameNameGameMode->GameReadyToStart())
	{
		InsertGameNameGameMode->StartPlay();
	}
}

void AMainPlayerController::OnPrimaryActionStart()
{
	PlayerCharacter->OnPrimaryActionStart();
}

void AMainPlayerController::OnPrimaryActionEnd()
{
	PlayerCharacter->OnPrimaryActionEnd();
}

void AMainPlayerController::SwitchNextWeapon()
{
	PlayerCharacter->SwitchNextWeapon();
}

void AMainPlayerController::SwitchPreviousWeapon()
{
	PlayerCharacter->SwitchPreviousWeapon();
}

void AMainPlayerController::MoveForward(float Value)
{
	PlayerCharacter->MoveForward(Value);
}

void AMainPlayerController::MoveRight(float Value)
{
	PlayerCharacter->MoveRight(Value);
}

void AMainPlayerController::AddControllerYawInput(float Value)
{
	PlayerCharacter->AddControllerYawInput(Value);
}

void AMainPlayerController::AddControllerPitchInput(float Value)
{
	PlayerCharacter->AddControllerPitchInput(Value);
}

void AMainPlayerController::TurnAtRate(float Value)
{
	PlayerCharacter->TurnAtRate(Value);
}

void AMainPlayerController::LookUpAtRate(float Value)
{
	PlayerCharacter->LookUpAtRate(Value);
}

void AMainPlayerController::BeginTouch(ETouchIndex::Type FingerIndex, UE::Math::TVector<double> Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnPrimaryActionStart();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AMainPlayerController::EndTouch(ETouchIndex::Type FingerIndex, UE::Math::TVector<double> Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

void AMainPlayerController::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	
}


bool AMainPlayerController::EnableTouchscreenMovement()
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMainPlayerController::BeginTouch);
		InputComponent->BindTouch(EInputEvent::IE_Released, this, &AMainPlayerController::EndTouch);

		return true;
	}
	
	return false;
}
