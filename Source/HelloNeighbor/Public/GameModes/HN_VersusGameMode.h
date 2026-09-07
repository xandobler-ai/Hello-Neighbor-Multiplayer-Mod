#pragma once

#include "CoreMinimal.h"
#include "GameModes/HN_GameModeBase.h"
#include "HN_VersusGameMode.generated.h"

/**
 * Competitive/Versus game mode
 * Players compete against each other for individual scores
 */
UCLASS()
class HELLONEIGHBOR_API AHN_VersusGameMode : public AHN_GameModeBase
{
    GENERATED_BODY()

public:
    AHN_VersusGameMode();

    virtual void BeginPlay() override;

protected:
    // Versus specific settings
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Versus")
    float MatchDurationSeconds;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Versus")
    int32 TargetScore;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Versus")
    bool bScoreLimitMode;

    virtual void InitializeGame() override;
    virtual void OnGameStateChanged() override;

public:
    /**
     * Award points to a player
     */
    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Versus")
    void AwardPoints(APlayerController* Player, int32 Points);

    /**
     * Get the winning player
     */
    UFUNCTION(BlueprintCallable, Category = "Versus")
    APlayerController* GetLeadingPlayer() const;

    /**
     * Check if match conditions are met
     */
    UFUNCTION(BlueprintCallable, Category = "Versus")
    bool IsMatchOver() const;

    /**
     * Get time remaining in match
     */
    UFUNCTION(BlueprintCallable, Category = "Versus")
    float GetTimeRemaining() const;
};
