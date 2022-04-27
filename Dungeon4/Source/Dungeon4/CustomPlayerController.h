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

protected:
	virtual void BeginPlay() override;
	
};
