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
	
}

// Called every frame
void ABoarder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ForwardVector = ForwardVector + (ForwardVelocity * GetActorForwardVector());
	FVector NewForward = FMath::VInterpTo(ForwardVector, ForwardVector.GetClampedToMaxSize(MaxVelocity), DeltaTime, Acceleration);
	ForwardVector.X = NewForward.X;
	ForwardVector.Y = NewForward.Y;
	ForwardVector.Z = NewForward.Z;
	NewRotation.Roll = GetActorRotation().Roll;
	SetActorLocation(FMath::VInterpTo(GetActorLocation(), GetActorLocation() + DesiredLocation + ForwardVector, DeltaTime, InterpSpeed));
	SetActorRotation(FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, RotationInterpSpeed));
	Rider->SetRelativeRotation(FMath::RInterpTo(Rider->RelativeRotation, NewRiderRotation, DeltaTime, RollSensitivity));


	if (TotalScore > TierTwoThreshold) {
		CurrentTierTheshold = TierThreeThreshold;
	} else if (TotalScore > TierOneThreshold) {
		CurrentTierTheshold = TierTwoThreshold;
	}
	AdjustCamera(DeltaTime);
}

// Called to bind functionality to input
void ABoarder::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveX", this, &ABoarder::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &ABoarder::Move_YAxis);

}

void ABoarder::Move_XAxis(float AxisValue)
{
	//DesiredLocation.X = (AxisValue * MovementSpeed);
	if (!Grounded) 
	{
		FRotator Rotator = FRotator(AxisValue * (InAirRotationSpeed / FlipModifier), 0.0f, 0.0f);
		AddActorWorldRotation(Rotator.Quaternion());
		TotalScore = TotalScore + (FMath::Abs(AxisValue) * InAirRotationSpeed);
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
		TotalScore = TotalScore + (FMath::Abs(AxisValue) * InAirRotationSpeed);
		//if (GEngine)
		//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Move YAxis Yaw: %f"), NewRotation.Yaw));
	}
}

void ABoarder::AdjustCamera(float DeltaTime)
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(CameraSpringArm->GetComponentLocation(), GetActorLocation());
	CameraSpringArm->SetWorldLocation(FMath::VInterpTo(CameraSpringArm->GetComponentLocation(),
		GetActorLocation() + (UKismetMathLibrary::GetForwardVector(LookAtRotation) * FVector(-CameraOffset, -CameraOffset, CameraOffset)), DeltaTime, CameraLocationLag));

	CameraSpringArm->SetWorldRotation(FMath::RInterpTo(CameraSpringArm->GetComponentRotation(), FRotator(LookAtRotation.Pitch, LookAtRotation.Yaw, 0.0f), DeltaTime, CameraRotationLag));
}



