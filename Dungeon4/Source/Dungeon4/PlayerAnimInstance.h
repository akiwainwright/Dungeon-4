// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON4_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void GetAnimationVariables();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player Movement")
	float velocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player Movement")
	bool isFalling;
	

	class APawn* Pawn;
};
