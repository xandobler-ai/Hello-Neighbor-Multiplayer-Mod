#include "Network/PlayerState.h"
#include "Net/UnrealNetwork.h"

AHN_PlayerState::AHN_PlayerState()
{
    PlayerScore = 0;
    KillCount = 0;
    DeathCount = 0;
    bIsTeamLeader = false;
}

void AHN_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AHN_PlayerState, PlayerScore);
    DOREPLIFETIME(AHN_PlayerState, KillCount);
    DOREPLIFETIME(AHN_PlayerState, DeathCount);
    DOREPLIFETIME(AHN_PlayerState, bIsTeamLeader);
}

void AHN_PlayerState::AddScore(int32 Points)
{
    if (HasAuthority())
    {
        PlayerScore += Points;
    }
}

void AHN_PlayerState::RecordKill()
{
    if (HasAuthority())
    {
        KillCount++;
    }
}

void AHN_PlayerState::RecordDeath()
{
    if (HasAuthority())
    {
        DeathCount++;
    }
}
