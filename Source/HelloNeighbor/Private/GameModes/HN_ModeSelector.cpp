#include "GameModes/HN_ModeSelector.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AHN_ModeSelector::AHN_ModeSelector()
{
    bReplicates = true;
    SelectedGameMode = EGameMode::CoOp;
}

void AHN_ModeSelector::BeginPlay()
{
    Super::BeginPlay();

    if (IsLocalPlayerController())
    {
        ShowModeSelection();
    }
}

void AHN_ModeSelector::ShowModeSelection()
{
    if (IsLocalPlayerController() && ModeSelectionWidgetClass)
    {
        if (CurrentWidget)
        {
            CurrentWidget->RemoveFromParent();
        }

        CurrentWidget = CreateWidget<UUserWidget>(this, ModeSelectionWidgetClass);
        if (CurrentWidget)
        {
            CurrentWidget->AddToViewport(100);
            UE_LOG(LogTemp, Warning, TEXT("Mode Selection Widget Displayed"));
        }
    }
}

void AHN_ModeSelector::HideModeSelection()
{
    if (CurrentWidget)
    {
        CurrentWidget->RemoveFromParent();
        CurrentWidget = nullptr;
    }
}

void AHN_ModeSelector::SelectGameMode(EGameMode GameMode)
{
    SelectedGameMode = GameMode;
    HideModeSelection();
    LoadGameModeLevel(GameMode);
}

void AHN_ModeSelector::LoadGameModeLevel(EGameMode GameMode)
{
    FString LevelName;

    switch (GameMode)
    {
        case EGameMode::CoOp:
            LevelName = TEXT("/Game/Maps/HN_CoopLevel");
            UE_LOG(LogTemp, Warning, TEXT("Loading Co-op Game Mode"));
            break;
        case EGameMode::Versus:
            LevelName = TEXT("/Game/Maps/HN_VersusLevel");
            UE_LOG(LogTemp, Warning, TEXT("Loading Versus Game Mode"));
            break;
        default:
            LevelName = TEXT("/Game/Maps/HN_CoopLevel");
            break;
    }

    // For now, just log the intent. In a real implementation, use OpenLevel
    // UGameplayStatics::OpenLevel(GetWorld(), *LevelName);
}
