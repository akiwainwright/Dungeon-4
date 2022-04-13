// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	
	

	//Making player face the right way when moving
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
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

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	

}

void APlayerCharacter::ZoomCamera(float inputValue)
{
	float currentArmLength = SpringArm->TargetArmLength;
	float newArmLength = currentArmLength - (inputValue * M_ZoomRate);

	SpringArm->TargetArmLength = FMath::Clamp(newArmLength, 600.0f, 900.0f);
}

void APlayerCharacter::MoveForwards(float inputValue)
{
	if(inputValue != 0)
	{
		GetCharacterMovement()->AddInputVector(FVector(inputValue, 0.0f, 0.0f));
		UE_LOG(LogTemp, Warning, TEXT("Character Velocity X:%f Y:%f Z:%f"), GetVelocity().X, GetVelocity().Y, GetVelocity().Z);
	}
}

void APlayerCharacter::MoveRight(float inputValue)
{
	if(inputValue != 0)
	{
		GetCharacterMovement()->AddInputVector(FVector(0.0f, inputValue, 0.0f));
		UE_LOG(LogTemp, Warning, TEXT("Character Velocity X:%f Y:%f Z:%f"), GetVelocity().X, GetVelocity().Y, GetVelocity().Z);
	}
}
