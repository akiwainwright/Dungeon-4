// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerWeapon.generated.h"

UCLASS()
class DUNGEON4_API APlayerWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
	USceneComponent* EffectSpawnLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Stats")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SFX")
	class USoundCue* SoundCue;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UStaticMeshComponent* GetMesh(){ return WeaponMesh;}
	void SetMesh(UStaticMeshComponent* mesh) { WeaponMesh = mesh;}

	UFUNCTION()
	void Hit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

};
