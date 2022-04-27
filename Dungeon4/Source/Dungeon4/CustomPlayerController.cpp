// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"

#include "Kismet/GameplayStatics.h"


void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySound2D(this, DungoenBGM);
}
