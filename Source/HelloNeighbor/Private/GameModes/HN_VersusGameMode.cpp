#include "GameModes/HN_VersusGameMode.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

AHN_VersusGameMode::AHN_VersusGameMode()
{
    MatchDurationSeconds = 600.0f; // 10 minutes
    TargetScore = 1000;
    bScoreLimitMode = false;
}

void AHN_VersusGameMode::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Versus Game Mode Started"));
}

void AHN_VersusGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AHN_VersusGameMode, MatchDurationSeconds);
    DOREPLIFETIME(AHN_VersusGameMode, TargetScore);
    DOREPLIFETIME(AHN_VersusGameMode, bScoreLimitMode);
}

void AHN_VersusGameMode::InitializeGame()
{
    Super::InitializeGame();
    UE_LOG(LogTemp, Warning, TEXT("Initializing Versus Mode - Match Duration: %.0f seconds"), MatchDurationSeconds);
}

void AHN_VersusGameMode::OnGameStateChanged()
{
    Super::OnGameStateChanged();
}

void AHN_VersusGameMode::AwardPoints(APlayerController* Player, int32 Points)
{
    if (!Player || (GetNetMode() != NM_ListenServer && GetNetMode() != NM_DedicatedServer))
        return;

    UE_LOG(LogTemp, Warning, TEXT("Player %s awarded %d points"), *Player->GetName(), Points);

    // TODO: Integrate with player state scoring system
}

APlayerController* AHN_VersusGameMode::GetLeadingPlayer() const
{
    // TODO: Determine and return the leading player
    return nullptr;
}

bool AHN_VersusGameMode::IsMatchOver() const
{
    if (bScoreLimitMode)
    {
        // TODO: Check if any player reached target score
        return false;
    }
    else
    {
        return GameTimer >= MatchDurationSeconds;
    }
}

float AHN_VersusGameMode::GetTimeRemaining() const
{
    float Remaining = MatchDurationSeconds - GameTimer;
    return FMath::Max(0.0f, Remaining);
}
