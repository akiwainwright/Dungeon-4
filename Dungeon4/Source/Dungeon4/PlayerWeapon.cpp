// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWeapon.h"

#include "CustomPlayerController.h"
#include "Enemies.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerWeapon::APlayerWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	SetRootComponent(WeaponMesh);

	EffectSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Effect"));
	EffectSpawnLocation->SetupAttachment(GetRootComponent());

	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Ignore);

}

// Called when the game starts or when spawned
void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();

	WeaponMesh->OnComponentBeginOverlap.AddDynamic(this, &APlayerWeapon::Hit);
	
}

// Called every frame
void APlayerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerWeapon::Hit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	APlayerCharacter* Player = nullptr;
	AEnemies* Enemy = nullptr;
	
	if(OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		Player =  Cast<APlayerCharacter>(OtherActor);
	}

	if(OtherActor->IsA(AEnemies::StaticClass()))
	{
		Enemy =  Cast<AEnemies>(OtherActor);
	}

	if(Player)
	{
		ACustomPlayerController* PlayerController = Cast<ACustomPlayerController>(Player->GetController());
		PlayerController->UpdateHealth(Damage);

		Player->PlayDamageEffect(EffectSpawnLocation->GetComponentLocation());
	}

	if(Enemy)
	{
		
		Enemy->PlayDamageEffect(EffectSpawnLocation->GetComponentLocation());
		Enemy->UpdateHealth(Damage);
	}

	UGameplayStatics::PlaySound2D(this, SoundCue);
}

