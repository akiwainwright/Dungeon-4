// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"

#include <string>

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ACustomPlayerController::BeginPlay()
{
	InputComponent->BindAction("LoseHealth", IE_Pressed, this, &ACustomPlayerController::DecreaseHealth);
	InputComponent->BindAction("Pause", IE_Pressed, this, &ACustomPlayerController::PauseGame);
	Super::BeginPlay();

	UGameplayStatics::PlaySound2D(this, DungoenBGM);

	Health = MaxHealth;

	if(HUDBase != nullptr)
	{
		HUD = CreateWidget(this, HUDBase);

		HUD->AddToViewport();
		HUD->SetVisibility(ESlateVisibility::Visible);

		UpdateHealthBar();
		UpdateRoomNumber();
	}
}

void ACustomPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PossessedPawn = InPawn;
}

void ACustomPlayerController::UpdateHealth(float healthChange)
{
	Health -= healthChange;

	if(Health > MaxHealth)
	{
		Health = MaxHealth;
	}

	if(Health <= 0)
	{
		if(bIsAlive)
		{
			if(HUD->GetName().Contains("Main"))
			{
				UpdateHealthBar();
			}
			bIsAlive = false;
			DeathSequence();
		}
	}
	else
	{
		if(HUD->GetName().Contains("Main"))
		{
			UpdateHealthBar();
		}
	}
	
}

void ACustomPlayerController::DecreaseHealth()
{
	UpdateHealth(-10.0f);

	if(Health <= 0)
	{
		PossessedPawn->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("YOU LOSE"));
	}
}

void ACustomPlayerController::CurrentRoom(int roomNumber)
{
	CurrentRoomNumber = roomNumber;

	if(HUD->GetName().Contains("Main"))
	{
		UpdateRoomNumber();
	}
}

void ACustomPlayerController::PauseGame()
{
	PauseScreen();
}
	
	
