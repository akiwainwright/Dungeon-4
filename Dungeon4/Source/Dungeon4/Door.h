// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class DUNGEON4_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Door Frame Mesh")
	UStaticMeshComponent* FrameMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Door Mesh")
	UStaticMeshComponent* DoorMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
