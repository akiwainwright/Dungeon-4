// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));
	RootComponent = FrameMesh;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Block"));
	DoorMesh->SetupAttachment(GetRootComponent());

	M_OpenSpeed = 1;
	M_Opened = false;
	
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	M_InitialLocation = DoorMesh->GetComponentLocation();
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::DoorOpened()
{
	M_Opened = true;
}

void ADoor::RaiseDoor(float raisedValue)
{
	FVector RaisedLocation = M_InitialLocation;
	RaisedLocation.Z += raisedValue;

	DoorMesh->SetWorldLocation(RaisedLocation);
}




