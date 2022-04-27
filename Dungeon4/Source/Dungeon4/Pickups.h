// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Pickups.generated.h"

UCLASS()
class DUNGEON4_API APickups : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickups();

	UFUNCTION(BlueprintNativeEvent)
	void PlayPickupEffect(USkeletalMeshComponent* PlayerMesh);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void PickupItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Collider")
	UBoxComponent* Collider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Mesh")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sound Effect")
	USoundCue* PickupSFX;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
