// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorSwitch.h"

#include "Door.h"

// Sets default values
ADoorSwitch::ADoorSwitch()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	RootComponent = TriggerBox;

	//Setting trigger box to only use overlaps and by default ignoring all channels
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	//Making collision respond to pawn
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Switch Mesh"));
	SwitchMesh->SetupAttachment(GetRootComponent());

	M_PlayerOnSwitch = false;
	M_PressDelay = 1.5f;
}

// Called when the game starts or when spawned
void ADoorSwitch::BeginPlay()
{
	Super::BeginPlay();
	M_InitialPosition = GetActorLocation();
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADoorSwitch::TriggerSwitch);	
}

// Called every frame
void ADoorSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADoorSwitch::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADoorSwitch::TriggerSwitch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	M_PlayerOnSwitch = true;
	if(!TargetDoor->DoorOpened())
	{
		GetWorldTimerManager().SetTimer(DoorSwitchPressDelay, this, &ADoorSwitch::SwitchTriggered, M_PressDelay);
	}
}

void ADoorSwitch::MovedOffSwitch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	M_PlayerOnSwitch = false;
}

void ADoorSwitch::LowerSwitch(float loweredValue)
{
	TargetDoor->DelayDoorOpening();
	FVector LoweredLocation = M_InitialPosition;
	LoweredLocation.Z += loweredValue;

	SetActorLocation(LoweredLocation);
}

void ADoorSwitch::SwitchTriggered()
{
	if(M_PlayerOnSwitch)
	{
		PressedSwitch();

		//if(!TargetDoor->DoorOpened())
		{
			TargetDoor->DelayDoorOpening();
		}
	}
}
