// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemies.generated.h"

UCLASS()
class DUNGEON4_API AEnemies : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemies();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Stats")
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Stats")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Stats")
	float Attack;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
