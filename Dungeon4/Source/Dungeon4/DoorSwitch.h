// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "DoorSwitch.generated.h"

UCLASS()
class DUNGEON4_API ADoorSwitch : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADoorSwitch();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Mesh")
	UStaticMeshComponent* SwitchMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Trigger Box")
	UBoxComponent* TriggerBox;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Door")
	class ADoor* TargetDoor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void TriggerSwitch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

};
