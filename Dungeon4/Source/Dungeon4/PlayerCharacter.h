// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerWeapon.h"
#include "Camera/CameraComponent.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class DUNGEON4_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character Mesh")
	USkeletalMeshComponent* CharacterMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Camera")
	UCameraComponent* Camera;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Light")
	UPointLightComponent* PlayerTorch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Throw Start Point")
	class USceneComponent* ThrowWeaponSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Combat")
	bool bIsAttacking;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat")
	class UAnimMontage* FightAnimMontage;

private:
	float M_ZoomRate;

	FName M_ProfileName;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ZoomCamera(float inputValue);
	void MoveForwards(float inputValue);
	void MoveRight(float inputValue);
	virtual void Jump() override;

	UFUNCTION(BlueprintImplementableEvent)
	void ThrowWeapon();

	void Attack();

	UFUNCTION(BlueprintCallable)
	void AttackFinished();
};


