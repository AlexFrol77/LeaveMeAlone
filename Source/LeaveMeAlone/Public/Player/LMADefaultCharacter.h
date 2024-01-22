// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LMADefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ULMAHealthComponent;
class UAnimMontage;
class ULMAWeaponComponent;

UCLASS()
class LEAVEMEALONE_API ALMADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ALMADefaultCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	ULMAHealthComponent* GetHealthComponent() const { return HealthComponent; }

	bool GetStateSprint();
	bool IsSprint = false;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY()
	UDecalComponent* CurrentCursor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float Stamina = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Health")
	ULMAHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	ULMAWeaponComponent* WeaponComponent;

private:

	float YRotation = -75.0f;
	float ArmLength = 1400.0f;
	float FOV = 55.0f;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Zoom(float Value);
	void ZoomIn();
	void ZoomOut();


	float MaxStamina = 100.0f;
	float SprintStamina = 20.0f;
	float StaminaRecovery = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float ZoomSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float MinZoomDistance = 250.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float MaxZoomDistance = 1300.0f;

	float CurrentZoomDistance = 500.0f;

	UFUNCTION(BlueprintCallable)
	void StartSprint();

	UFUNCTION(BlueprintCallable)
	void StopSprint();

	void OnDeath();

	void OnHealthChanged(float NewHealth);

	void RotationPlayerOnCursor();
};
