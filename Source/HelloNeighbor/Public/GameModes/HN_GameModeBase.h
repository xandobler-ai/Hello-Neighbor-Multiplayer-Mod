#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HN_GameModeBase.generated.h"

/**
 * Base game mode for Hello Neighbor multiplayer mod
 * Handles core game state and replication
 */
UCLASS()
class HELLONEIGHBOR_API AHN_GameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    AHN_GameModeBase();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

protected:
    // Game state tracking
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Multiplayer")
    int32 MaxPlayers;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Multiplayer")
    float GameTimer;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Multiplayer")
    bool bGameActive;

    // Timer handles
    FTimerHandle GameTimerHandle;

    /**
     * Initialize the game mode
     */
    virtual void InitializeGame();

    /**
     * Called when game state changes
     */
    virtual void OnGameStateChanged();

    /**
     * Update game timer
     */
    void UpdateGameTimer();

public:
    /**
     * Get current game timer
     */
    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    float GetGameTimer() const { return GameTimer; }

    /**
     * Check if game is active
     */
    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    bool IsGameActive() const { return bGameActive; }

    /**
     * Start the game
     */
    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Multiplayer")
    virtual void StartGame();

    /**
     * End the game
     */
    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Multiplayer")
    virtual void EndGame();

    /**
     * Reset the game
     */
    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Multiplayer")
    virtual void ResetGame();
};
