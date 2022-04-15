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

private:
	float M_OpenSpeed;
	
	bool M_Opened;
	
	FVector M_OpenedOffset;
	FVector M_InitialLocation;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool GetDoorState() { return M_Opened; }
	void DoorOpened();

	UFUNCTION(BlueprintImplementableEvent, Category="Open Door")
	void OpenDoor();

	UFUNCTION(BlueprintCallable)
	void RaiseDoor(float raisedValue);
};
