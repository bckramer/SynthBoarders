// Fill out your copyright notice in the Description page of Project Settings.


#include "Boarder.h"

// Sets default values
ABoarder::ABoarder()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	SetRootComponent(CollisionComp);
	AddInstanceComponent(CollisionComp);
	Rider = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rider"));
	Board = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Board"));
	Board->SetupAttachment(Rider);

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(Rider);
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void ABoarder::BeginPlay()
{
	Super::BeginPlay();
	CurrentTierTheshold = TierOneThreshold;
	OriginalForwardVelocity = MaxVelocity;
	OriginalMovementSpeed = MovementSpeed;
	
}

// Called every frame
void ABoarder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Victory) {
		ForwardVector.Y = 0.0f;
		ForwardVector = ForwardVector + (ForwardVelocity * GetActorForwardVector());
		FVector NewForward = FMath::VInterpTo(ForwardVector, ForwardVector.GetClampedToMaxSize(MaxVelocity), DeltaTime, Acceleration);
		ForwardVector.X = FMath::Clamp(NewForward.X, 0.0f, MaxVelocity);
		if (Grounded) {
			ForwardVector.Y = ForwardVector.Y * MovementSpeed;
		}
		else 
		{
			ForwardVector.Y = NewForward.Z;
		}
		if (Grounded) {
			ForwardVector.Z = -100.0f;
		}
		else {
			ForwardVector.Z = NewForward.Z;
		}

		// if (GEngine)
		//  	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("X: %f Y: %f Z: %f"), ForwardVector.X, ForwardVector.Y, ForwardVector.Z));
		NewRotation.Roll = GetActorRotation().Roll;
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), GetActorLocation() + ForwardVector, DeltaTime, InterpSpeed));
		SetActorRotation(FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, RotationInterpSpeed));
		Rider->SetRelativeRotation(FMath::RInterpTo(Rider->RelativeRotation, NewRiderRotation, DeltaTime, RollSensitivity));

		if (TotalScore > TierThreeThreshold) {
			VisualizerThree->SetActorScale3D(FVector(10.0f, 10.0f, 10.0f));
		}
		else if (TotalScore > TierTwoThreshold) {
			CurrentTierTheshold = TierThreeThreshold;
			VisualizerTwo->SetActorScale3D(FVector(10.0f, 10.0f, 10.0f));
		}
		else if (TotalScore > TierOneThreshold) {
			VisualizerOne->SetActorScale3D(FVector(10.0f, 10.0f, 10.0f));
			CurrentTierTheshold = TierTwoThreshold;
		}

		if (CleanLanding && Grounded && PotentialPoints > 0) {
			TotalScore = TotalScore + PotentialPoints;
			PotentialPoints = 0;
			//ForwardVector.Z = ForwardVector.Z - 100.0f;
		}
		if (!CleanLanding && Grounded && PotentialPoints > 0) {
			PotentialPoints = 0;
			//ForwardVector.Z = ForwardVector.Z - 100.0f;
		}
		if (GetActorLocation().X > 127990.0f) {
			Victory = true;
		}
	}
	if (GetActorLocation().Z <= 0) {
		SetActorLocation(LastGroundedLocation);
		CameraSpringArm->SetWorldLocation(GetActorLocation());
	}

	AdjustCamera(DeltaTime);
}

// Called to bind functionality to input
void ABoarder::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveX", this, &ABoarder::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &ABoarder::Move_YAxis);
	InputComponent->BindAxis("Boost", this, &ABoarder::Boost);

}

void ABoarder::Move_XAxis(float AxisValue)
{
	//DesiredLocation.X = (AxisValue * MovementSpeed);
	if (!Grounded) 
	{
		FRotator Rotator = FRotator(AxisValue * (InAirRotationSpeed / FlipModifier), 0.0f, 0.0f);
		AddActorWorldRotation(Rotator.Quaternion());
		PotentialPoints = PotentialPoints + (FMath::Abs(AxisValue) * InAirRotationSpeed);
		//if (GEngine)
		//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Move XAxis Pitch: %f"), NewRotation.Pitch));
	}
}

void ABoarder::Move_YAxis(float AxisValue)
{
	//DesiredLocation.Y = (AxisValue * MovementSpeed);
	if (Grounded)
	{
		NewRiderRotation.Roll = (AxisValue * RollSpeed);
		NewRotation.Yaw = FMath::Clamp(GetActorRotation().Yaw + (AxisValue * RotationSpeed), -MaxRotation, MaxRotation);
	}
	else
	{
		NewRotation.Yaw = GetActorRotation().Yaw + (AxisValue * InAirRotationSpeed);
		PotentialPoints = PotentialPoints + (FMath::Abs(AxisValue) * InAirRotationSpeed);
		//if (GEngine)
		//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Move YAxis Yaw: %f"), NewRotation.Yaw));
	}
}

void ABoarder::Boost(float AxisValue)
{
	if (Grounded)
	{
		MaxVelocity = OriginalForwardVelocity + ((MaxVelocity / 2.0f) * AxisValue);
		MovementSpeed = OriginalMovementSpeed / 3.0f;
	}
}

void ABoarder::AdjustCamera(float DeltaTime)
{
	FVector Forward = UKismetMathLibrary::GetForwardVector(GetActorRotation());
	float ExtraZ = 0.0f;
	if (!Grounded) {
		ExtraZ = 1000.0f;
	}
	else if (Forward.Z > 0.0f) {
		ExtraZ = (Forward.Z * 500.0f);
	}


	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(CameraSpringArm->GetComponentLocation(), GetActorLocation());
	CameraSpringArm->SetWorldLocation(FMath::VInterpTo(CameraSpringArm->GetComponentLocation(),
		GetActorLocation() + (UKismetMathLibrary::GetForwardVector(LookAtRotation) * FVector(CameraOffset, 0.0f, -ZBuffer - ExtraZ)), DeltaTime, CameraLocationLag));

	CameraSpringArm->SetWorldRotation(FMath::RInterpTo(CameraSpringArm->GetComponentRotation(), FRotator(LookAtRotation.Pitch, LookAtRotation.Yaw, 0.0f), DeltaTime, CameraRotationLag));
}



