#include "Network/GameState.h"
#include "Net/UnrealNetwork.h"

AHN_GameState::AHN_GameState()
{
    TotalPlayersConnected = 0;
    bGameInProgress = false;
}

void AHN_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AHN_GameState, TotalPlayersConnected);
    DOREPLIFETIME(AHN_GameState, bGameInProgress);
}
