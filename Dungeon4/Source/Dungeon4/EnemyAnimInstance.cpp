// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"

#include "Enemies.h"

void UEnemyAnimInstance::UpdateAnimationVariables()
{
	if(!Pawn)
	{
		Pawn = TryGetPawnOwner();
		Enemies = Cast<AEnemies>(Pawn);
	}
	else
	{
		if(Enemies)
		{
			FVector Velocity = Enemies->GetVelocity();
			Speed = FVector(Velocity.X, Velocity.Y, 0.0f).Size();
			EnemyState = Enemies->CurrentState;
		}
	}
}
