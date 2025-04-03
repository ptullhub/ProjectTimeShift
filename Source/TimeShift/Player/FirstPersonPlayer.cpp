#include "Timeshift/Player/FirstPersonPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFirstPersonPlayer::AFirstPersonPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// Camera setup
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AFirstPersonPlayer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFirstPersonPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update head tilt effect
	UpdateHeadTilt(DeltaTime);
}

// Called to bind functionality to input
void AFirstPersonPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis("MoveForwardBackward", this, &AFirstPersonPlayer::MoveForwardBackward);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &AFirstPersonPlayer::MoveLeftRight);
	PlayerInputComponent->BindAxis("CameraPitch", this, &AFirstPersonPlayer::CameraPitch);
	PlayerInputComponent->BindAxis("CameraYaw", this, &AFirstPersonPlayer::CameraYaw);
}

void AFirstPersonPlayer::MoveForwardBackward(float inputAxis)
{
	FVector forwardDir = GetActorForwardVector();
	AddMovementInput(forwardDir, inputAxis);
}

void AFirstPersonPlayer::MoveLeftRight(float inputAxis)
{
	FVector rightDir = GetActorRightVector();
	AddMovementInput(rightDir, inputAxis);
}

void AFirstPersonPlayer::CameraPitch(float inputY)
{
	AddControllerPitchInput(inputY);
}

void AFirstPersonPlayer::CameraYaw(float inputX)
{
	AddControllerYawInput(inputX);
}

void AFirstPersonPlayer::UpdateHeadTilt(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("Hello"));
	// Get character velocity and check if moving
	float Speed = GetVelocity().Size();
	bool bIsMoving = Speed > 0;

	// Check if character is NOT falling
	bool bIsOnGround = GetCharacterMovement()->IsMovingOnGround();

	// Get input axis value
	float StrafeInput = GetInputAxisValue("MoveLeftRight");
	bool bIsStrafing = FMath::Abs(StrafeInput) > 0;

	// Determine if tilting should happen
	if (bIsMoving && bIsOnGround && bIsStrafing)
	{
		// Determine lean direction
		float TargetTilt = (StrafeInput > 0) ? -LeanAngle : LeanAngle;

		// Apply interpolation for smooth transition
		FRotator CurrentRotation = GetControlRotation();
		FRotator TargetRotation = FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw, TargetTilt);
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, LeanInterpSpeed);

		// Set control rotation
		GetController()->SetControlRotation(NewRotation);
	}
	else
	{
		// Reset tilt when not moving or strafing
		FRotator CurrentRotation = GetControlRotation();
		FRotator TargetRotation = FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw, 0.0f);
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, LeanInterpSpeed);

		// Set control rotation
		GetController()->SetControlRotation(NewRotation);
	}
}
