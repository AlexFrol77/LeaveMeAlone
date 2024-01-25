// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEAVEMEALONE_API ULMAHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	ULMAHealthComponent();

	UFUNCTION(BlueprintCallable)
	float GetHealth() const {return Health;}

	FOnDeath OnDeath;

	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable)
	bool IsDead() const;

	UFUNCTION(BlueprintCallable)
	void SetHealthFull();

	void AddFullHealth();

	bool AddHealth(float NewHealth);
	bool IsHealthFull() const;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 0.0f;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, 
						const class UDamageType* DamageType, 
						class AController* InstigatedBy, 
						AActor* DamageCauser);
};
