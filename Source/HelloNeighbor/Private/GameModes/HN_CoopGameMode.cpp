#include "GameModes/HN_CoopGameMode.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

AHN_CoopGameMode::AHN_CoopGameMode()
{
    SharedObjectiveCount = 5;
    CompletedObjectives = 0;
    SharedTimeLimitSeconds = 600.0f; // 10 minutes
}

void AHN_CoopGameMode::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Co-op Game Mode Started"));
}

void AHN_CoopGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AHN_CoopGameMode, SharedObjectiveCount);
    DOREPLIFETIME(AHN_CoopGameMode, CompletedObjectives);
    DOREPLIFETIME(AHN_CoopGameMode, SharedTimeLimitSeconds);
}

void AHN_CoopGameMode::InitializeGame()
{
    Super::InitializeGame();
    UE_LOG(LogTemp, Warning, TEXT("Initializing Co-op Mode with %d objectives"), SharedObjectiveCount);
}

void AHN_CoopGameMode::OnGameStateChanged()
{
    Super::OnGameStateChanged();
}

void AHN_CoopGameMode::CompleteObjective()
{
    if (GetNetMode() == NM_ListenServer || GetNetMode() == NM_DedicatedServer)
    {
        CompletedObjectives++;
        UE_LOG(LogTemp, Warning, TEXT("Objective Completed: %d/%d"), CompletedObjectives, SharedObjectiveCount);

        if (AreAllObjectivesComplete())
        {
            EndGame();
            UE_LOG(LogTemp, Warning, TEXT("All Objectives Complete! Co-op Victory!"));
        }
    }
}

float AHN_CoopGameMode::GetObjectiveProgress() const
{
    if (SharedObjectiveCount <= 0)
        return 0.0f;

    return (float)CompletedObjectives / (float)SharedObjectiveCount;
}

bool AHN_CoopGameMode::AreAllObjectivesComplete() const
{
    return CompletedObjectives >= SharedObjectiveCount;
}

void AHN_CoopGameMode::BroadcastTeamMessage(const FString& Message)
{
    if (GetNetMode() == NM_ListenServer || GetNetMode() == NM_DedicatedServer)
    {
        UE_LOG(LogTemp, Warning, TEXT("Team Message: %s"), *Message);
    }
}
