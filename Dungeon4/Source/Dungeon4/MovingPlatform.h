// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class DUNGEON4_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Mesh")
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Moving Platform")
	int Direction;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Moving Platform")
	float WaitTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	FVector M_InitialLocation;
	FRotator M_InitialRotation;

	//Sin Amplitude - A
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true), Category="Moving Platform")
	float M_MoveRange; //Double this will be the range of motion for the platform

	//Sin Period - B 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true), Category="Moving Platform")
	float M_PlatformSpeed;

	//Sin Phase Shift - C
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true), Category="Moving Platform")
	float M_StartPosition; //Initial X Value of Sin Graph
	
	float M_VerticalShift;

	float M_SinXValue;

	bool bWait;

	FTimerHandle WaitTimeHandler;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CheckWait();
};


