// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Sound/SoundCue.h"
#include "CustomPlayerController.generated.h"

/**
 * 
 */

UCLASS()
class DUNGEON4_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BGM")
	USoundCue* DungoenBGM;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="HUD")
	TSubclassOf<class UUserWidget> HUDBase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="HUD")
	UUserWidget* HUD;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Player Stats")
	float MaxHealth = 150.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Player Stats")
	float Health = 75.0f;
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthBar();

	void UpdateHealth(float healthChange);

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent();
	
};
