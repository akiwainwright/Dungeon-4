// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"

#include "CustomPlayerController.h"
#include "GameFramework/Character.h"

void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickup::PickupItem);
}

void AHealthPickup::PickupItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::PickupItem(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	ACharacter* player = Cast<ACharacter>(OtherActor);
	ACustomPlayerController* PlayerController = Cast<ACustomPlayerController>(player->GetController());
	PlayerController->UpdateHealth(-30.0f);

	UE_LOG(LogTemp, Warning, TEXT("Remaining Health: %f"), PlayerController->Health);
	Destroy();
}
