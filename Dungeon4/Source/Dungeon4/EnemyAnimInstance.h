// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON4_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationVariables();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation Variables")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation Variables")
	class APawn* Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation Variables")
	class AEnemies* Enemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation Variables")
	EnemyStates EnemyState;
	
};
