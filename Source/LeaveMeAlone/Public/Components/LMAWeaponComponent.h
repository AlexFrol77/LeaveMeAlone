// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAWeaponComponent.generated.h"

class ALMABaseWeapon;
class UAnimMontage;
class ALMADefaultCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEAVEMEALONE_API ULMAWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	ULMAWeaponComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, 
							   FActorComponentTickFunction* ThisTickFunction) override;

	void Fire();
	void StopFire();
	void Reload();

	UFUNCTION(BlueprintCallable)
	bool GetCurrentWeaponAmmo(FAmmoWeapon& AmmoWeapon);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ALMABaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UAnimMontage* ReloadMontage;

	UFUNCTION(BlueprintCallable)
	void SetFullAmmo();

private:

	UPROPERTY()
	ALMABaseWeapon* Weapon = nullptr;

	bool AnimReloading = false;

	bool AmmoBullets = true;
	bool AmmoClips = true;

	void SpawnWeapon();
	void InitAnimNotify();

	void OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh);

	void CheckAmmoClips();
};
