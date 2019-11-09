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
	
}

// Called every frame
void ABoarder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector forwardVector = ForwardVelocity * GetActorForwardVector();
	NewRotation.Roll = GetActorRotation().Roll;
	NewRotation.Pitch = GetActorRotation().Pitch;
	SetActorLocation(FMath::VInterpTo(GetActorLocation(), GetActorLocation() + DesiredLocation + forwardVector, DeltaTime, InterpSpeed));
	SetActorRotation(FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, RotationInterpSpeed));
	Rider->SetRelativeRotation(FMath::RInterpTo(Rider->RelativeRotation, NewRiderRotation, DeltaTime, RollSensitivity));

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
	DesiredLocation.X = (AxisValue * MovementSpeed);
}

void ABoarder::Move_YAxis(float AxisValue)
{
	//DesiredLocation.Y = (AxisValue * MovementSpeed);
	NewRiderRotation.Roll = (AxisValue * RollSpeed);
	NewRotation.Yaw = FMath::Clamp(GetActorRotation().Yaw + (AxisValue * RotationSpeed), -MaxRotation, MaxRotation);
}

void ABoarder::AdjustCamera(float DeltaTime)
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(CameraSpringArm->GetComponentLocation(), GetActorLocation());
	CameraSpringArm->SetWorldLocation(FMath::VInterpTo(CameraSpringArm->GetComponentLocation(),
		GetActorLocation() + (UKismetMathLibrary::GetForwardVector(LookAtRotation) * FVector(-CameraOffset, -CameraOffset, CameraOffset)), DeltaTime, CameraLocationLag));

	CameraSpringArm->SetWorldRotation(FMath::RInterpTo(CameraSpringArm->GetComponentRotation(), FRotator(LookAtRotation.Pitch, LookAtRotation.Yaw, 0.0f), DeltaTime, CameraRotationLag));
}



