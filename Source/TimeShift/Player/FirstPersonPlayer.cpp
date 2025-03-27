// Fill out your copyright notice in the Description page of Project Settings.


#include "Timeshift/Player/FirstPersonPlayer.h"
#include "Camera/CameraComponent.h"

// Sets default values
AFirstPersonPlayer::AFirstPersonPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

