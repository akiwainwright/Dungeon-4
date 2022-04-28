// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups.h"

#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickups::APickups()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Item Collider"));
	SetRootComponent(Collider);

	Collider->SetCollisionObjectType(ECC_WorldStatic);
	Collider->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMesh->SetupAttachment(GetRootComponent());

}

void APickups::PlayPickupEffect_Implementation(USkeletalMeshComponent* PlayerMesh)
{
	
}

// Called when the game starts or when spawned
void APickups::BeginPlay()
{
	Super::BeginPlay();
}

void APickups::PickupItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Picked Up Item"));
		OtherActor = Cast<APlayerCharacter>(OtherActor);

		USkeletalMeshComponent* mesh = OtherActor->FindComponentByClass<USkeletalMeshComponent>();
		
		PlayPickupEffect(mesh);
		
		 if(PickupSFX != nullptr)
		 {
		 	UGameplayStatics::PlaySound2D(this, PickupSFX);
		 }
	}
}
// Called every frame
void APickups::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

