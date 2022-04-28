// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomTrigger.h"

#include "CustomPlayerController.h"
#include "PlayerCharacter.h"

// Sets default values
ARoomTrigger::ARoomTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Zone"));
	SetRootComponent(TriggerBox);

	TriggerBox->SetCollisionObjectType(ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

// Called when the game starts or when spawned
void ARoomTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ARoomTrigger::SetCurrentRoom);
}

void ARoomTrigger::SetCurrentRoom(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		ACharacter* player = Cast<ACharacter>(OtherActor);

		ACustomPlayerController* PlayerController = Cast<ACustomPlayerController>(player->GetController());

		if(PlayerController->CurrentRoomNumber != RoomNumber)
		{
			PlayerController->CurrentRoomNumber = RoomNumber;
			PlayerController->UpdateRoomNumber();
		}
	}
}

// Called every frame
void ARoomTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

