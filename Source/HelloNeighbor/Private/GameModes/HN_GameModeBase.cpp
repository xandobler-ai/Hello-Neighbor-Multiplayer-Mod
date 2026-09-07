#include "GameModes/HN_GameModeBase.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

AHN_GameModeBase::AHN_GameModeBase()
{
    // Enable replication
    bReplicates = true;
    bNetLoadOnClient = true;

    // Game settings
    MaxPlayers = 4;
    GameTimer = 0.0f;
    bGameActive = false;
}

void AHN_GameModeBase::BeginPlay()
{
    Super::BeginPlay();

    if (GetNetMode() == NM_ListenServer || GetNetMode() == NM_DedicatedServer)
    {
        InitializeGame();
    }
}

void AHN_GameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bGameActive && (GetNetMode() == NM_ListenServer || GetNetMode() == NM_DedicatedServer))
    {
        UpdateGameTimer();
    }
}

void AHN_GameModeBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AHN_GameModeBase, MaxPlayers);
    DOREPLIFETIME(AHN_GameModeBase, GameTimer);
    DOREPLIFETIME(AHN_GameModeBase, bGameActive);
}

void AHN_GameModeBase::InitializeGame()
{
    UE_LOG(LogTemp, Warning, TEXT("Initializing Hello Neighbor Multiplayer Game Mode"));
    OnGameStateChanged();
}

void AHN_GameModeBase::OnGameStateChanged()
{
    // Override in derived classes
}

void AHN_GameModeBase::UpdateGameTimer()
{
    if (bGameActive)
    {
        GameTimer += GetWorldDeltaSeconds();
    }
}

void AHN_GameModeBase::StartGame()
{
    if (GetNetMode() == NM_ListenServer || GetNetMode() == NM_DedicatedServer)
    {
        bGameActive = true;
        GameTimer = 0.0f;
        UE_LOG(LogTemp, Warning, TEXT("Game Started"));
    }
}

void AHN_GameModeBase::EndGame()
{
    if (GetNetMode() == NM_ListenServer || GetNetMode() == NM_DedicatedServer)
    {
        bGameActive = false;
        UE_LOG(LogTemp, Warning, TEXT("Game Ended"));
    }
}

void AHN_GameModeBase::ResetGame()
{
    if (GetNetMode() == NM_ListenServer || GetNetMode() == NM_DedicatedServer)
    {
        bGameActive = false;
        GameTimer = 0.0f;
        UE_LOG(LogTemp, Warning, TEXT("Game Reset"));
    }
}
