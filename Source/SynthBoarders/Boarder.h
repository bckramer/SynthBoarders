// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "Boarder.generated.h"

UCLASS()
class SYNTHBOARDERS_API ABoarder : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABoarder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USpringArmComponent* CameraSpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* MainCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* Rider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* Board;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float MovementSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float ForwardVelocity = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float MaxVelocity = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float RotationSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float InAirRotationSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float FlipModifier = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float RotationInterpSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float MaxRotation = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float RollSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float RollSensitivity = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float InterpSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float Acceleration = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool Grounded = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool CleanLanding = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float CameraOffset = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float CameraLocationLag = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float CameraRotationLag = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ZBuffer = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
		int TotalScore = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
		int PotentialPoints = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
		int CurrentTierTheshold = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
		int PreviousTierTheshold = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
		int TierOneThreshold = 2000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
		int TierTwoThreshold = 8000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
		int TierThreeThreshold = 16000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector ForwardVector = FVector(0.0f, 0.0f, 0.0f);
	FVector DesiredLocation = FVector(0.0f, 0.0f, 0.0f);
	FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);
	FRotator NewRiderRotation = FRotator(0.0f, 0.0f, 0.0f);

	//Input functions
	void AdjustCamera(float DeltaTime);
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);

};