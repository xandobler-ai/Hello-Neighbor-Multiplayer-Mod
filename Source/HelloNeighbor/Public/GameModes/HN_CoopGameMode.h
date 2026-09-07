#pragma once

#include "CoreMinimal.h"
#include "GameModes/HN_GameModeBase.h"
#include "HN_CoopGameMode.generated.h"

/**
 * Co-operative game mode
 * Players work together to complete shared objectives
 */
UCLASS()
class HELLONEIGHBOR_API AHN_CoopGameMode : public AHN_GameModeBase
{
    GENERATED_BODY()

public:
    AHN_CoopGameMode();

    virtual void BeginPlay() override;

protected:
    // Co-op specific settings
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "CoOp")
    int32 SharedObjectiveCount;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "CoOp")
    int32 CompletedObjectives;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "CoOp")
    float SharedTimeLimitSeconds;

    virtual void InitializeGame() override;
    virtual void OnGameStateChanged() override;

public:
    /**
     * Complete an objective
     */
    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "CoOp")
    void CompleteObjective();

    /**
     * Get progress towards victory
     */
    UFUNCTION(BlueprintCallable, Category = "CoOp")
    float GetObjectiveProgress() const;

    /**
     * Check if all objectives are complete
     */
    UFUNCTION(BlueprintCallable, Category = "CoOp")
    bool AreAllObjectivesComplete() const;

    /**
     * Broadcast team message to all players
     */
    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "CoOp")
    void BroadcastTeamMessage(const FString& Message);
};
