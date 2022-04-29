// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowingWeapon.h"

// Sets default values
AThrowingWeapon::AThrowingWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AThrowingWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThrowingWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

