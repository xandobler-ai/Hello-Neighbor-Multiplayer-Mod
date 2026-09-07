#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerState.generated.h"

/**
 * Custom player state for multiplayer tracking
 */
UCLASS()
class HELLONEIGHBOR_API AHN_PlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    AHN_PlayerState();

protected:
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player")
    int32 PlayerScore;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player")
    int32 KillCount;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player")
    int32 DeathCount;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player")
    bool bIsTeamLeader;

public:
    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Player")
    void AddScore(int32 Points);

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Player")
    void RecordKill();

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Player")
    void RecordDeath();

    UFUNCTION(BlueprintCallable, Category = "Player")
    int32 GetPlayerScore() const { return PlayerScore; }

    UFUNCTION(BlueprintCallable, Category = "Player")
    int32 GetKillCount() const { return KillCount; }

    UFUNCTION(BlueprintCallable, Category = "Player")
    int32 GetDeathCount() const { return DeathCount; }
};
