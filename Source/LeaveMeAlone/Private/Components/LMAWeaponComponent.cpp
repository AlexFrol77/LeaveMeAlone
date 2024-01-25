// LeaveMeAlone Game by Netologiya. All RightsReserved.

#include "Components/LMAWeaponComponent.h"
#include "Animations/LMAReloadFinishedAnimNotify.h"
#include "GameFramework/Character.h"
#include "LMABaseWeapon.h"
#include "Player/LMADefaultCharacter.h"

ULMAWeaponComponent::ULMAWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULMAWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapon();
	InitAnimNotify();
	Weapon->ReloadDelegate.AddUObject(this, &ULMAWeaponComponent::Reload);
	Weapon->EmptyAmmoClipsDelegate.AddUObject(this, &ULMAWeaponComponent::CheckAmmoClips);
}

void ULMAWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void ULMAWeaponComponent::SpawnWeapon()
{
	Weapon = GetWorld()->SpawnActor<ALMABaseWeapon>(WeaponClass);
	if (Weapon)
	{
		const auto Character = Cast<ACharacter>(GetOwner());
		if (Character)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, "r_Weapon_Socket");
		}
	}
}

void ULMAWeaponComponent::Fire()
{
	if (Weapon && !AnimReloading)
	{
		ALMADefaultCharacter* DefaultCharacter = Cast<ALMADefaultCharacter>(GetOwner());
		if (!DefaultCharacter->IsSprint)
		{
			Weapon->Fire();
		}
	}
}

void ULMAWeaponComponent::StopFire()
{
		Weapon->StopFire();	
}

void ULMAWeaponComponent::InitAnimNotify()
{
	if (!ReloadMontage)
	{ 
		return;
	}
		
	const auto NotifiesEvents = ReloadMontage->Notifies;
	for (auto NotifyEvent : NotifiesEvents)
	{
		auto ReloadFinish = Cast<ULMAReloadFinishedAnimNotify>(NotifyEvent.Notify);
		if (ReloadFinish)
		{
			ReloadFinish->OnNotifyReloadFinished.AddUObject(this, &ULMAWeaponComponent::OnNotifyReloadFinished);
			break;
		}
	}
}

void ULMAWeaponComponent::OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh)
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (Character->GetMesh() == SkeletalMesh)
	{
		AnimReloading = false;
	}
}

void ULMAWeaponComponent::CheckAmmoClips()
{
	AmmoClips = false;
}

void ULMAWeaponComponent::Reload()
{
	if (Weapon->GetAmmoBullets())
	{
		if (AmmoClips)
		{
			Weapon->ChangeClip();
			AnimReloading = true;
			ACharacter* Character = Cast<ACharacter>(GetOwner());
			Character->PlayAnimMontage(ReloadMontage);
		}
	}
}

bool ULMAWeaponComponent::GetCurrentWeaponAmmo(FAmmoWeapon& AmmoWeapon)
{
	if (Weapon)
	{
		AmmoWeapon = Weapon->GetCurrentAmmoWeapon();
		
		return true;
	}
	return false;
}

void ULMAWeaponComponent::SetFullAmmo() 
{
	Weapon->SetFullAmmo();
}