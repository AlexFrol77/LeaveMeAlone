// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Animations/LMAReloadFinishedAnimNotify.h"

void ULMAReloadFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotifyReloadFinished.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}