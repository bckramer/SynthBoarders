// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
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
		float RotationSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float RotationCorrectionSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float MaxRotation = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float InterpSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ZBuffer = 3.0f;


	FVector DesiredLocation = FVector(0.0f, 0.0f, 0.0f);

	//Input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);

};