// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/OutputDeviceNull.h"
#include "GameFramework/Character.h"
#include "FirstPersonPlayer.generated.h"

UCLASS()
class TIMESHIFT_API AFirstPersonPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstPersonPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:

	// Define camera component class and mark as editable anywhere
	UPROPERTY(EditAnywhere);
	class UCameraComponent* Camera;

	// Define movement functions
	void MoveForwardBackward(float inputAxis);
	void MoveLeftRight(float inputAxis);

	void CameraPitch(float inputY);
	void CameraYaw(float inputX);

	// Head Tilt Function
	void UpdateHeadTilt(float DeltaTime);

	// Leaning angle
	UPROPERTY(EditAnywhere, Category = "Head Tilt")
	float LeanAngle = 5.0f;

	// Interpolation Speed
	UPROPERTY(EditAnywhere, Category = "Head Tilt")
	float LeanInterpSpeed = 5.0f;

};
