#include "FPSGameState.h"
#include "FPSPlayerController.h"
#include "Engine/World.h"



void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		AFPSPlayerController* PC = Cast<AFPSPlayerController>(It->Get());
		if (PC && PC->IsLocalController())
		{
			PC->OnMissionCompleted(InstigatorPawn, bMissionSuccess);

			//Disable Input
			APawn* MyPawn = PC->GetPawn();
			if (PC)
			{
				MyPawn->DisableInput(PC);
			}
		}

	}
}
