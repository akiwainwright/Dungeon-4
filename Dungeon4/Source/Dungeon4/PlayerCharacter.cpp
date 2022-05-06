// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "PlayerAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	M_ProfileName = "Player";
	GetCapsuleComponent()->SetCollisionProfileName(M_ProfileName);
	//Setting up the spring arm for camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 700.0f;
	SpringArm->SetRelativeRotation(FRotator(-70.0f, 0.0f, 0.0f));
	
	//Preventing the camera from rotating with the camera
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	
	M_ZoomRate = 40.0f;

	//Setting up camera to be attached to spring arm
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	//Adding torch for player to see in the dungeon
	PlayerTorch = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	PlayerTorch->SetupAttachment(GetRootComponent());
	PlayerTorch->Intensity = 10000.0f;
	PlayerTorch->AttenuationRadius = 750.0f;

	//Making player face the right way when moving
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	GetCharacterMovement()->AirControl = 1.5f;

	bIsAttacking = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("CameraZoom", this, &APlayerCharacter::ZoomCamera);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForwards);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::Attack);
	

}

void APlayerCharacter::ZoomCamera(float inputValue)
{
	float currentArmLength = SpringArm->TargetArmLength;
	float newArmLength = currentArmLength - (inputValue * M_ZoomRate);

	SpringArm->TargetArmLength = FMath::Clamp(newArmLength, 600.0f, 900.0f);
}

void APlayerCharacter::MoveForwards(float inputValue)
{
	if(inputValue != 0 && !bIsAttacking)
	{
		GetCharacterMovement()->AddInputVector(FVector(inputValue, 0.0f, 0.0f));
	}
}

void APlayerCharacter::MoveRight(float inputValue)
{
	if(inputValue != 0 && !bIsAttacking)
	{
		GetCharacterMovement()->AddInputVector(FVector(0.0f, inputValue, 0.0f));
	}
}

void APlayerCharacter::Jump()
{
	if(!bIsAttacking)
	{
		Super::Jump();
	}
}

void APlayerCharacter::Attack()
{
	if(!bIsAttacking && GetCharacterMovement()->IsWalking())
	{
		bIsAttacking = true;
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if(!AnimInstance->IsA(UPlayerAnimInstance::StaticClass()) && !FightAnimMontage)
		{
			return;
		}
		UPlayerAnimInstance* PlayerAnimInstance = Cast<UPlayerAnimInstance>(AnimInstance);

		int FightMontageSection = FMath::RandRange(0, 2);

		switch (FightMontageSection)
		{
			case 0:
			{
					PlayerAnimInstance->Montage_Play(FightAnimMontage, 2.2f);
					PlayerAnimInstance->Montage_JumpToSection(FName("Slash"), FightAnimMontage);
				break;
			}
			case 1:
			{
					PlayerAnimInstance->Montage_Play(FightAnimMontage, 2.75f);
					PlayerAnimInstance->Montage_JumpToSection(FName("OutSlash"), FightAnimMontage);
				break;
			}
			case 2:
			{
					PlayerAnimInstance->Montage_Play(FightAnimMontage, 2.75f);
					PlayerAnimInstance->Montage_JumpToSection(FName("InSlash"), FightAnimMontage);
				break;
			}
			default:
				break;
		}
	}
}

void APlayerCharacter::AttackFinished()
{
	bIsAttacking = false;
}

void APlayerCharacter::BeginAttackFrames()
{
	Weapon->WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void APlayerCharacter::EndAttackFrames()
{
	Weapon->WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
