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