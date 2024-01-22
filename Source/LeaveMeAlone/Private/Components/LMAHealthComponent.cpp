// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Components/LMAHealthComponent.h"

ULMAHealthComponent::ULMAHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void ULMAHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	OnHealthChanged.Broadcast(Health);

	AActor* OwnerComponent = GetOwner();
	if (OwnerComponent)
	{
		OwnerComponent->OnTakeAnyDamage.AddDynamic(this, &ULMAHealthComponent::OnTakeAnyDamage);
	}
}
	
// Called every frame
void ULMAHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULMAHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, 
										  const UDamageType* DamageType, 
	                                      AController* InstigatedBy, 
	                                      AActor* DamageCauser)
{
	if (IsDead())
		return;

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	OnHealthChanged.Broadcast(Health);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}

bool ULMAHealthComponent::IsDead() const
{
	return Health <= 0.0f;
}

bool ULMAHealthComponent::AddHealth(float NewHealth)
{
	if (IsDead() || IsHealthFull())
		return false;

	Health = FMath::Clamp(Health + NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
	return true;
}

bool ULMAHealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}