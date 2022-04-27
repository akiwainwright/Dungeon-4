// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Mesh"));
	PlatformMesh->SetupAttachment(GetRootComponent());

	M_MoveRange = 450.0f; //Platform move range from start position is double this
	M_PlatformSpeed = 1.0f; //Speed at which the platform moves
	M_StartPosition = 0.0f; //Startpoint on sin graph
	M_VerticalShift = 0.0f;

	M_SinXValue = 0.0f;

	Direction = 1;

	bWait = false;
	WaitTime = 0.5f;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	M_InitialLocation = GetActorLocation();
	M_InitialRotation = GetActorRotation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NextLocation = GetActorLocation();

	if(!bWait)
	{
		if(M_InitialRotation.Yaw == 0)
		{
			NextLocation.Y = M_InitialLocation.Y + (Direction * (M_MoveRange * sin(M_PlatformSpeed * (M_SinXValue + M_StartPosition) + M_VerticalShift)));
			
			if(NextLocation.Y <= M_InitialLocation.Y - M_MoveRange + 1.0f || NextLocation.Y >= M_InitialLocation.Y + M_MoveRange - 1.0f)
			{
				bWait = !bWait;
				GetWorldTimerManager().SetTimer(WaitTimeHandler, this, &AMovingPlatform::CheckWait, WaitTime);
			}
		}
		else
		{
			NextLocation.X = M_InitialLocation.X + (Direction * (M_MoveRange * sin(M_PlatformSpeed * (M_SinXValue + M_StartPosition) + M_VerticalShift)));
			
			if(NextLocation.X <= M_InitialLocation.X - M_MoveRange + 1.0f || NextLocation.X >= M_InitialLocation.X + M_MoveRange - 1.0f)
			{
				bWait = !bWait;
				GetWorldTimerManager().SetTimer(WaitTimeHandler, this, &AMovingPlatform::CheckWait, WaitTime);
			}
		}


		SetActorRelativeLocation(NextLocation);

		M_SinXValue += DeltaTime;
	}
}

void AMovingPlatform::CheckWait()
{
	bWait = false;
}

