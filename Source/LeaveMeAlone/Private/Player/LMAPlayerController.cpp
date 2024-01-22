// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Player/LMAPlayerController.h"

ALMAPlayerController::ALMAPlayerController() 
{

}

void ALMAPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void ALMAPlayerController::BeginSpectatingState()
{
	SetControlRotation(FRotator(-75.0f, 0.0f, 0.0f));
	Super::BeginSpectatingState();
}