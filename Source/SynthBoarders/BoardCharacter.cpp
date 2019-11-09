// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardCharacter.h"

// Sets default values
ABoardCharacter::ABoardCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoardCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoardCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoardCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

