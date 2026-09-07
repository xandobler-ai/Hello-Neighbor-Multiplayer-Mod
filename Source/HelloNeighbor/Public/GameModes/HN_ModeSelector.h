#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HN_ModeSelector.generated.h"

class UUserWidget;

/**
 * Mode selection controller
 * Handles the selection between Co-op and Versus game modes
 */
UCLASS()
class HELLONEIGHBOR_API AHN_ModeSelector : public APlayerController
{
    GENERATED_BODY()

public:
    AHN_ModeSelector();

    virtual void BeginPlay() override;

    /**
     * Game mode options
     */
    UENUM(BlueprintType)
    enum class EGameMode : uint8
    {
        CoOp = 0 UMETA(DisplayName = "Co-operative"),
        Versus = 1 UMETA(DisplayName = "Competitive/Versus")
    };

protected:
    // UI Widget class for mode selection
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UUserWidget> ModeSelectionWidgetClass;

    // Currently displayed widget
    UPROPERTY(BlueprintReadOnly, Category = "UI")
    UUserWidget* CurrentWidget;

    // Selected game mode
    UPROPERTY(BlueprintReadWrite, Category = "Gameplay")
    EGameMode SelectedGameMode;

public:
    /**
     * Show the mode selection UI
     */
    UFUNCTION(BlueprintCallable, Category = "UI")
    void ShowModeSelection();

    /**
     * Hide the mode selection UI
     */
    UFUNCTION(BlueprintCallable, Category = "UI")
    void HideModeSelection();

    /**
     * Select a game mode and start the game
     */
    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void SelectGameMode(EGameMode GameMode);

    /**
     * Get the selected game mode
     */
    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    EGameMode GetSelectedGameMode() const { return SelectedGameMode; }

    /**
     * Load the appropriate game mode level/map
     */
    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void LoadGameModeLevel(EGameMode GameMode);
};
