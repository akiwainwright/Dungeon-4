// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies.h"

#include "AIController.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemies::AEnemies()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyVision = CreateDefaultSubobject<USphereComponent>(TEXT("Enemy Vision"));
	EnemyVision->SetupAttachment(GetRootComponent());
	EnemyVision->SetSphereRadius(600.0f);

	AttackRange = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Range"));
	AttackRange->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AEnemies::BeginPlay()
{
	Super::BeginPlay();
	EnemyController = Cast<AAIController>(GetController());

	EnemyVision->OnComponentBeginOverlap.AddDynamic(this, &AEnemies::PlayerEnteredVision);
	EnemyVision->OnComponentEndOverlap.AddDynamic(this, &AEnemies::PlayerLeftVision);
	AttackRange->OnComponentBeginOverlap.AddDynamic(this, &AEnemies::PlayerEnteredAttackRange);
	AttackRange->OnComponentEndOverlap.AddDynamic(this, &AEnemies::PlayerLeftAttackRange);
}

// Called every frame
void AEnemies::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemies::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemies::PlayerEnteredVision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InPursuitRange = true;
	SetCurrentState(EnemyStates::EnemyState_Pursue);
	PursuePlayer(OtherActor);
}

void AEnemies::PlayerLeftVision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InPursuitRange = false;
	SetCurrentState(EnemyStates::EnemyState_Idle);
	StopPursuing();
}

void AEnemies::PlayerEnteredAttackRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InAttackRange = true;
	StopPursuing();
	SetCurrentState(EnemyStates::EnemyState_Attack);
}

void AEnemies::PlayerLeftAttackRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InAttackRange = false;
	
	if(CurrentState != EnemyStates::EnemyState_Attack)
	{
		if(InPursuitRange)
		{
			PursuePlayer(OtherActor);
		}
		else
		{
			StopPursuing();
		}
	}
}

