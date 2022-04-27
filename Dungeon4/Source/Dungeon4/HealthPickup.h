// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON4_API AHealthPickup : public APickups
{
	GENERATED_BODY()

public:

protected:
	virtual void BeginPlay() override;
	virtual void PickupItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
