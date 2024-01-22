// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "LMABaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeapon, All, All);

ALMABaseWeapon::ALMABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	SetRootComponent(WeaponComponent);
}

void ALMABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentAmmoWeapon = AmmoWeapon;
}

void ALMABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALMABaseWeapon::Fire()
{
	StartShoot();
}

void ALMABaseWeapon::StopFire()
{
	StopShoot();
}

void ALMABaseWeapon::StartShoot()
{
	IsShooting = true;

	GetWorldTimerManager().SetTimer(TimerHandle_Shoot, this, &ALMABaseWeapon::Shoot, 0.1f, true);
}

void ALMABaseWeapon::StopShoot()
{

	IsShooting = false;

	GetWorldTimerManager().ClearTimer(TimerHandle_Shoot);
}

void ALMABaseWeapon::Shoot()
{
	if (IsCurrentClipEmpty())
	{
		return;
	}

	const FTransform SocketTransform = WeaponComponent->GetSocketTransform("Muzzle");
	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceDistance;
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Black, false, 1.0f, 0, 2.0f);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);

	if (HitResult.bBlockingHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 24, FColor::Red, false, 1.0f);
	}

	DecrementBullets();

	if (!IsShooting)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Shoot);
	}
}

void ALMABaseWeapon::DecrementBullets()
{
	CurrentAmmoWeapon.Bullets--;
	UE_LOG(LogWeapon, Display, TEXT("Bullets = %s"), *FString::FromInt(CurrentAmmoWeapon.Bullets));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, 
		*FString::FromInt(CurrentAmmoWeapon.Bullets), true, FVector2D(2.0f, 2.0f));
	if (IsCurrentClipEmpty())
	{
		ReloadDelegate.Broadcast();
		IsShooting = false;
		ChangeClip();
	}
}

bool ALMABaseWeapon::IsCurrentClipEmpty() const
{
	return CurrentAmmoWeapon.Bullets == 0;
}

void ALMABaseWeapon::ChangeClip()
{
	if (CurrentAmmoWeapon.Clips != 0)
	{
		CurrentAmmoWeapon.Bullets = AmmoWeapon.Bullets;
		CurrentAmmoWeapon.Clips--;
	}
	if (CurrentAmmoWeapon.Clips == 0)
	{
		EmptyAmmoClipsDelegate.Broadcast();
	}	
}

bool ALMABaseWeapon::GetAmmoBullets()
{
	if (CurrentAmmoWeapon.Bullets == 30)
	{
		return false;
	}
	
	return true;
}