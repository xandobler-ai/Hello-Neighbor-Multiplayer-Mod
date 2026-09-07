#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MultiplayerCharacter.generated.h"

/**
 * Networked character for multiplayer gameplay
 * Handles player representation, movement replication, and state synchronization
 */
UCLASS()
class HELLONEIGHBOR_API AMultiplayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMultiplayerCharacter();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    // Player identification
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Multiplayer")
    int32 PlayerIndex;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Multiplayer")
    FString PlayerName;

    // Movement replication
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Movement")
    FVector ReplicatedLocation;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Movement")
    FRotator ReplicatedRotation;

    // Player state
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "State")
    bool bIsAlive;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "State")
    float Health;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State")
    float MaxHealth;

    // Movement input
    FVector MovementInput;
    FRotator LookInput;

public:
    /**
     * Set the player's name
     */
    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    void SetPlayerName(const FString& NewName);

    /**
     * Get player name
     */
    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    FString GetPlayerName() const { return PlayerName; }

    /**
     * Take damage
     */
    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "State")
    void TakeDamage(float DamageAmount);

    /**
     * Heal the character
     */
    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "State")
    void Heal(float HealAmount);

    /**
     * Check if character is alive
     */
    UFUNCTION(BlueprintCallable, Category = "State")
    bool IsAlive() const { return bIsAlive; }

    /**
     * Respawn the character
     */
    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "State")
    void Respawn();

protected:
    /**
     * Handle movement input
     */
    void MoveForward(float Value);
    void MoveRight(float Value);
    void LookUp(float Value);
    void TurnRight(float Value);

    /**
     * Replicate movement to other clients
     */
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void ReplicateMovement();
};
