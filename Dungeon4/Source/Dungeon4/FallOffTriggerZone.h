// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallOffTriggerZone.generated.h"

UCLASS()
class DUNGEON4_API AFallOffTriggerZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFallOffTriggerZone();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Trigger Box")
	class UBoxComponent* TriggerZone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Reset Position")
	class APawn* ResetPosition;

	FTimerHandle PositionResetTimer;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	float M_PositionResetDelay;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ResetPlayerPosition(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
};
