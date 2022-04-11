// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

#include "GameFramework/PawnMovementComponent.h"

void UPlayerAnimInstance::GetAnimationVariables()
{
	if(Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}
	else
	{
		FVector CurrentVelocity = Pawn->GetVelocity();
		velocity = CurrentVelocity.Size();

		isFalling = Pawn->GetMovementComponent()->IsFalling();
	}
}
