// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMAHealthPickup.generated.h"

class USphereComponent;
class ALMADefaultCharacter;

UCLASS()
class LEAVEMEALONE_API ALMAHealthPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALMAHealthPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* SphereComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float RespawnTime = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")//, meta = (ClampMin = "5.0f", ClampMax = "100.0f"))
	float HealthFromPickup = 100.0f;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	bool GivePickup(ALMADefaultCharacter* Character);
	void PickupWasTaken();
	void RespawnPickup();

};
