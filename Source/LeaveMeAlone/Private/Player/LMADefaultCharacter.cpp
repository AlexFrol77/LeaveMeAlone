// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Player/LMADefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ALMADefaultCharacter::ALMADefaultCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = ArmLength;
	SpringArmComponent->SetRelativeRotation(FRotator(YRotation, 0.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bEnableCameraLag = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetFieldOfView(FOV);
	CameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

}

// Called when the game starts or when spawned
void ALMADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (CursorMaterial)
	{
		CurrentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), 
						CursorMaterial, CursorSize, FVector(0));
	}
	CurrentZoomDistance = (MinZoomDistance + MaxZoomDistance) / 2.0f;
}

// Called every frame
void ALMADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		FHitResult ResultHit;
		PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);
		float FindRotatorResultYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ResultHit.Location).Yaw;
		SetActorRotation(FQuat(FRotator(0.0f, FindRotatorResultYaw, 0.0f)));
		if (CurrentCursor)
		{
			CurrentCursor->SetWorldLocation(ResultHit.Location);
		}
	}

	if (!IsSprint && Stamina < MaxStamina)
	{
		Stamina += StaminaRecovery * DeltaTime;
		Stamina = FMath::Clamp(Stamina, 0.0f, MaxStamina);
	}

	if (IsSprint)
	{
		Stamina -= SprintStamina * DeltaTime;
		if (Stamina <= 0.0f)
		{
			Stamina = 0.0f;
			StopSprint();
		}
	}
}

// Called to bind functionality to input
void ALMADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALMADefaultCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALMADefaultCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Zoom", this, &ALMADefaultCharacter::Zoom);
	PlayerInputComponent->BindAction("MoveSprint", IE_Pressed, this, &ALMADefaultCharacter::StartSprint);
	PlayerInputComponent->BindAction("MoveSprint", IE_Released, this, &ALMADefaultCharacter::StopSprint);
}

void ALMADefaultCharacter::MoveForward(float Value) 
{
	AddMovementInput(GetActorForwardVector(), Value);
}


void ALMADefaultCharacter::MoveRight(float Value) 
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ALMADefaultCharacter::ZoomIn()
{
	CurrentZoomDistance -= ZoomSpeed;
	CurrentZoomDistance = FMath::Clamp(CurrentZoomDistance, MinZoomDistance, MaxZoomDistance);
	SpringArmComponent->TargetArmLength = CurrentZoomDistance;
}

void ALMADefaultCharacter::ZoomOut()
{
	CurrentZoomDistance += ZoomSpeed;
	CurrentZoomDistance = FMath::Clamp(CurrentZoomDistance, MinZoomDistance, MaxZoomDistance);
	SpringArmComponent->TargetArmLength = CurrentZoomDistance;
}

void ALMADefaultCharacter::StartSprint()
{
	ACharacter* Character = Cast<ACharacter>(this);

	if (Character && Stamina >= SprintStamina)
	{
		UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
		IsSprint = true;
		if (MovementComponent)
		{
			MovementComponent->MaxWalkSpeed = 600.0f;
		}
	}
}

void ALMADefaultCharacter::StopSprint()
{
	ACharacter* Character = Cast<ACharacter>(this);
	if (Character)
	{
		UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
		IsSprint = false;
		if (MovementComponent)
		{
			MovementComponent->MaxWalkSpeed = 300.0f;
		}
	}
}

void ALMADefaultCharacter::Zoom(float Value)
{
	if (Value > 0)
	{
		ZoomIn();
	}
	else if (Value < 0)
	{
		ZoomOut();
	}
}

