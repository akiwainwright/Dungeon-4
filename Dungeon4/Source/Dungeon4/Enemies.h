// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemies.generated.h"

UENUM(BlueprintType)
enum class EnemyStates : uint8
{
	EnemyState_Idle		UMETA(DeplayName = "Idle"),
	EnemyState_Pursue		UMETA(DeplayName = "Pursue"),
	EnemyState_Attack		UMETA(DeplayName = "Attack"),	
};

UCLASS()
class DUNGEON4_API AEnemies : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemies();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy Controller")
	class AAIController* EnemyController;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Stats")
	class USphereComponent* EnemyVision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Stats")
	class USphereComponent* AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Equipped weapon")
	class APlayerWeapon* Weapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Stats")
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Stats")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Stats")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy State")
	EnemyStates CurrentState;

	UFUNCTION(BlueprintCallable)
	void SetCurrentState(EnemyStates NextState) { CurrentState = NextState; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	bool InPursuitRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	bool InAttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	bool bCanTakeDamate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	bool bIsAlive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	class UUserWidget* HealthBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="Animation")
	class UAnimMontage* FightMontage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void PlayerEnteredVision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	virtual void PlayerLeftVision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	virtual void PlayerEnteredAttackRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	virtual void PlayerLeftAttackRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void PursuePlayer(AActor* PursueTarget);

	UFUNCTION(BlueprintImplementableEvent)
	void StopPursuing();

	void UpdateHealth(float Damage);

	UFUNCTION(BlueprintCallable)
	void BeginAttackFrames();

	UFUNCTION(BlueprintCallable)
	void EndAttackFrames();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthBar();

	UFUNCTION(BlueprintImplementableEvent)
	void AttackPlayer();

	UFUNCTION(BlueprintImplementableEvent)
	void DecreaseEnemyCount();

	UFUNCTION(BlueprintCallable)
	void AttackAgain() { AttackPlayer();}

	UFUNCTION(BlueprintImplementableEvent)
	void DeathSequence();

	UFUNCTION(BlueprintCallable)
	void DestroyObject();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayDamageEffect(FVector Location);
	

};
