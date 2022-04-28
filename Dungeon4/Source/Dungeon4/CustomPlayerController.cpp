// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"

#include <string>

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySound2D(this, DungoenBGM);

	if(HUDBase != nullptr)
	{
		HUD = CreateWidget(this, HUDBase);

		HUD->AddToViewport();
		HUD->SetVisibility(ESlateVisibility::Visible);

		UpdateHealthBar();
	}
}

void ACustomPlayerController::UpdateHealth(float healthChange)
{
	Health += healthChange;

	if(HUD->GetName().Contains("Main"))
	{
		UpdateHealthBar();
	}
}

float ACustomPlayerController::GetHealthPercent()
{
	return Health/MaxHealth;
}
	
	
