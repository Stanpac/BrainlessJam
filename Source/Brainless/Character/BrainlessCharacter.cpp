// Copyright Epic Games, Inc. All Rights Reserved.

#include "BrainlessCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Brainless.h"


ABrainlessCharacter::ABrainlessCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	SetRootComponent(GetCapsuleComponent());
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	// CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	// CameraBoom->SetupAttachment(RootComponent);
	// CameraBoom->TargetArmLength = 400.0f;
	// CameraBoom->bUsePawnControlRotation = true;

	// Create a camera
	// Camera->SetupAttachment(RootComponent);
	// Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	// Camera->bUsePawnControlRotation = false;
}

void ABrainlessCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABrainlessCharacter::Move);
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Triggered, this, &ABrainlessCharacter::Throw);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABrainlessCharacter::Look);
	}
	else
	{
		UE_LOG(LogBrainless, Error, TEXT("%s : Failed to find an Enhanced Input component!"), *GetNameSafe(this));
	}
}

void ABrainlessCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (GetController() != nullptr)
	{
		// find out which way is forward
		// const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator Rotation = GetController()->GetViewTarget()->GetActorRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * SpeedFactor;

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) * SpeedFactor;
		
		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

// TODO : Use Controller Rotation For Throwing Direction ! 
void ABrainlessCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

// TODO : Implement Throw Function ! 
/*
void ABrainlessCharacter::Throw(const FInputActionValue& Value)
{
	
}
*/

