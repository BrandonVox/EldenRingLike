#include "EldenCharacter.h"
#include "GameFramework/SpringArmComponent.h" // Camera boom
#include "Camera/CameraComponent.h" // Follow camera

AEldenCharacter::AEldenCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	// Camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;

	// Follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

}

void AEldenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AEldenCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

//void AEldenCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}


