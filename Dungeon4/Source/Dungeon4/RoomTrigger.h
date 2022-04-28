// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "RoomTrigger.generated.h"

UCLASS()
class DUNGEON4_API ARoomTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomTrigger();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room Trigger Box")
	UBoxComponent* TriggerBox;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Room Trigger Box")
	int RoomNumber;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void SetCurrentRoom(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
