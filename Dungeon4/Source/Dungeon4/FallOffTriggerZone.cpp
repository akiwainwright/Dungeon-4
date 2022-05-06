// Fill out your copyright notice in the Description page of Project Settings.


#include "FallOffTriggerZone.h"

#include "CustomPlayerController.h"
#include "PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

// Sets default values
AFallOffTriggerZone::AFallOffTriggerZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Zone"));
	RootComponent = TriggerZone;

	TriggerZone->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerZone->SetCollisionObjectType(ECC_WorldStatic);
	TriggerZone->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerZone->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

// Called when the game starts or when spawned
void AFallOffTriggerZone::BeginPlay()
{
	Super::BeginPlay();
	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &AFallOffTriggerZone::ResetPlayerPosition);
	
}

// Called every frame
void AFallOffTriggerZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFallOffTriggerZone::ResetPlayerPosition(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
		Player->SetActorLocation(ResetPosition->GetActorLocation());

		ACustomPlayerController* PlayerController = Cast<ACustomPlayerController>(Player->GetController());
		PlayerController->UpdateHealth(PlayerController->MaxHealth * 0.2f);
	}
}

