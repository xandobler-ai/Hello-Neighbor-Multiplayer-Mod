#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameState.generated.h"

/**
 * Custom game state for multiplayer tracking
 */
UCLASS()
class HELLONEIGHBOR_API AHN_GameState : public AGameState
{
    GENERATED_BODY()

public:
    AHN_GameState();

protected:
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game")
    int32 TotalPlayersConnected;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game")
    bool bGameInProgress;

public:
    UFUNCTION(BlueprintCallable, Category = "Game")
    int32 GetTotalPlayersConnected() const { return TotalPlayersConnected; }

    UFUNCTION(BlueprintCallable, Category = "Game")
    bool IsGameInProgress() const { return bGameInProgress; }
};
