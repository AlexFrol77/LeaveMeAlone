// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMABaseWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE(FReload)
DECLARE_MULTICAST_DELEGATE(FEmptyAmmoBullets)
DECLARE_MULTICAST_DELEGATE(FEmptyAmmoClips)

class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FAmmoWeapon
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite;
};

UCLASS()
class LEAVEMEALONE_API ALMABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	ALMABaseWeapon();

	virtual void Tick(float DeltaTime) override;

	void Fire();
	void StopFire(); 
	void ChangeClip();

	bool GetAmmoBullets();

	void SetFullAmmo();

	FReload ReloadDelegate;

	FEmptyAmmoClips EmptyAmmoClipsDelegate;

	FAmmoWeapon GetCurrentAmmoWeapon() const { return CurrentAmmoWeapon; }

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceDistance = 800.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoWeapon AmmoWeapon{30, 1, false};

	FTimerHandle TimerHandle_Shoot;

	void StartShoot();
	void StopShoot();

	void Shoot();

	void DecrementBullets();
	bool IsCurrentClipEmpty() const;
	
private:

	FAmmoWeapon CurrentAmmoWeapon;

	bool IsShooting;

};
