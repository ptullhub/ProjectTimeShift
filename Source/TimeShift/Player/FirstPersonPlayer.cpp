#include "Timeshift/Player/FirstPersonPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AFirstPersonPlayer::AFirstPersonPlayer()
{
	// Set this character to call Tick() every frame.
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

	// Apply head tilt based on movement input
	HeadTilt(DeltaTime);
}

// Called to bind functionality to input
void AFirstPersonPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Basic movement control bindings
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

void AFirstPersonPlayer::HeadTilt(float deltaTime)
{
	// Get lateral movement input
	float MoveInput = GetInputAxisValue("MoveLeftRight");

	// UE_LOG(LogTemp, Warning, TEXT("HeadTilt Called - MoveInput: %f"), MoveInput);

	// Define max tilt angle (adjust for preference)
	float MaxTiltAngle = 80.0f;

	// Target tilt based on movement direction
	float TargetRoll = MoveInput * MaxTiltAngle; 

	// Interpolate smoothly
	FRotator CurrentRotation = Camera->GetRelativeRotation();
	float NewRoll = FMath::FInterpTo(CurrentRotation.Roll, TargetRoll, deltaTime, 5.0f);

	// Apply new tilt to camera
	Camera->SetRelativeRotation(FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw, NewRoll));
}
