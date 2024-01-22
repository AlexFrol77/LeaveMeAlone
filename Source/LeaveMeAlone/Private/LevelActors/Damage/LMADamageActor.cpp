// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "LevelActors/Damage/LMADamageActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALMADamageActor::ALMADamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetSphereRadius(SphereRadius);
	SetRootComponent(SphereComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(SphereComponent);
	StaticMesh->SetRelativeScale3D(FVector(2.0f, 2.0f, 0.05f));
	StaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -4.0f));

}

// Called when the game starts or when spawned
void ALMADamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALMADamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), 
										SphereRadius, nullptr, {}, this, nullptr, false);
}

