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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	float M_MoveSpeed;

	FVector M_InitialLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true), Category="Moving Platform")
	float M_Amplitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true), Category="Moving Platform")
	float M_Period;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true), Category="Moving Platform")
	float M_PhaseShift;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true), Category="Moving Platform")
	float M_VerticalShift;

	float M_SinXValue;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};


