// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Mesh"));
	PlatformMesh->SetupAttachment(GetRootComponent());

	M_Amplitude = 450.0f; //Platform move range from start position is double this
	M_Period = 1.0f; //Speed at which the platform moves
	M_PhaseShift = -90.0f; //Startpoint on sin graph
	M_VerticalShift = 0.0f;

	M_SinXValue = 0.0f;
	

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	M_InitialLocation = GetActorLocation();	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NextLocation = GetActorLocation();

	FRotator currentRotation = GetActorRotation();

	if(currentRotation.Yaw == 0)
	{
		NextLocation.Y = M_InitialLocation.Y + (M_Amplitude * sin(M_Period * (M_SinXValue + M_PhaseShift) + M_VerticalShift));
	}
	else
	{
		NextLocation.X = M_InitialLocation.X + (M_Amplitude * sin(M_Period * (M_SinXValue + M_PhaseShift) + M_VerticalShift));
	}

	

	SetActorRelativeLocation(NextLocation);

	M_SinXValue += DeltaTime;

	//stopping sin x value continuously getting bigger
	// if(M_SinXValue > 360)
	// {
	// 	M_SinXValue -= 360;
	// }
}

