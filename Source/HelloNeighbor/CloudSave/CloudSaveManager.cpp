#include "CloudSave/CloudSaveManager.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"

void UCloudSaveManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	bCloudConnected = false;
	bEnableAutoSync = true;
	AutoSyncInterval = 300.0f; // 5 minutes
	LocalStoragePath = FPaths::ProjectSavedDir() + TEXT("SaveGames/");
	CloudStoragePath = TEXT("https://api.example.com/cloud-saves/"); // Replace with actual cloud service

	InitializeCloudConnection();
	StartAutoSync();

	UE_LOG(LogTemp, Warning, TEXT("CloudSaveManager initialized"));
}

void UCloudSaveManager::Deinitialize()
{
	StopAutoSync();
	Super::Deinitialize();

	UE_LOG(LogTemp, Warning, TEXT("CloudSaveManager deinitialized"));
}

void UCloudSaveManager::SaveGameToCloud(const FCloudSaveData& SaveData)
{
	CurrentSaveData = SaveData;
	CurrentSaveData.LastSaveTime = FDateTime::Now();

	// Save to local storage first
	FString SaveFilePath = LocalStoragePath + SaveData.PlayerId + TEXT(".sav");
	FString JsonString = FString::Printf(
		TEXT("{\"PlayerId\":\"%s\",\"CurrentLevel\":%d,\"CurrentScore\":%.2f,\"TotalPlayTime\":%d}"),
		*SaveData.PlayerId, SaveData.CurrentLevel, SaveData.CurrentScore, SaveData.TotalPlayTime
	);

	if (FFileHelper::SaveStringToFile(JsonString, *SaveFilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Save data saved locally for player: %s"), *SaveData.PlayerId);

		// Attempt cloud upload
		if (bCloudConnected)
		{
			// In a real implementation, this would upload to a cloud service
			OnCloudSaveComplete.Broadcast(true, TEXT("Save successful"));
			UE_LOG(LogTemp, Warning, TEXT("Save data uploaded to cloud for player: %s"), *SaveData.PlayerId);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cloud not connected, save stored locally"));
			OnCloudSaveComplete.Broadcast(true, TEXT("Saved locally (cloud unavailable)"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to save local data for player: %s"), *SaveData.PlayerId);
		OnCloudSaveComplete.Broadcast(false, TEXT("Save failed"));
	}
}

void UCloudSaveManager::LoadGameFromCloud(const FString& PlayerId)
{
	FString SaveFilePath = LocalStoragePath + PlayerId + TEXT(".sav");

	// Try to load from local storage first
	FString JsonString;
	if (FFileHelper::LoadFileToString(JsonString, *SaveFilePath))
	{
		CurrentSaveData.PlayerId = PlayerId;
		CurrentSaveData.LastSaveTime = FDateTime::Now();

		UE_LOG(LogTemp, Warning, TEXT("Save data loaded for player: %s"), *PlayerId);
		OnCloudLoadComplete.Broadcast(true, CurrentSaveData);
	}
	else if (bCloudConnected)
	{
		// Try to load from cloud if local not found
		UE_LOG(LogTemp, Warning, TEXT("Local save not found, attempting cloud load for player: %s"), *PlayerId);
		OnCloudLoadComplete.Broadcast(false, CurrentSaveData);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not load save data for player: %s"), *PlayerId);
		OnCloudLoadComplete.Broadcast(false, CurrentSaveData);
	}
}

void UCloudSaveManager::SyncWithCloud()
{
	if (!bCloudConnected)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cloud not connected, skipping sync"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Syncing with cloud for player: %s"), *CurrentSaveData.PlayerId);

	// In a real implementation, this would sync bidirectionally with cloud service
	SaveGameToCloud(CurrentSaveData);
}

void UCloudSaveManager::MergeCloudData(const FCloudSaveData& LocalData, const FCloudSaveData& CloudData)
{
	// Simple merge strategy: use the most recent data
	if (CloudData.LastSaveTime > LocalData.LastSaveTime)
	{
		CurrentSaveData = CloudData;
		UE_LOG(LogTemp, Warning, TEXT("Cloud data is newer, merged for player: %s"), *CloudData.PlayerId);
	}
	else
	{
		CurrentSaveData = LocalData;
		UE_LOG(LogTemp, Warning, TEXT("Local data is newer, merged for player: %s"), *LocalData.PlayerId);
	}
}

void UCloudSaveManager::BackupLocalSave(const FString& PlayerId)
{
	FString SourcePath = LocalStoragePath + PlayerId + TEXT(".sav");
	FString BackupPath = LocalStoragePath + PlayerId + TEXT("_backup.sav");

	if (IFileManager::Get().Copy(*BackupPath, *SourcePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Backup created for player: %s"), *PlayerId);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create backup for player: %s"), *PlayerId);
	}
}

void UCloudSaveManager::RestoreFromBackup(const FString& PlayerId)
{
	FString SourcePath = LocalStoragePath + PlayerId + TEXT("_backup.sav");
	FString RestorePath = LocalStoragePath + PlayerId + TEXT(".sav");

	if (IFileManager::Get().Copy(*RestorePath, *SourcePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Restored from backup for player: %s"), *PlayerId);
		LoadGameFromCloud(PlayerId);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to restore from backup for player: %s"), *PlayerId);
	}
}

void UCloudSaveManager::InitializeCloudConnection()
{
	// In a real implementation, this would establish connection to cloud service
	// For now, we'll assume connection is established
	bCloudConnected = true;
	UE_LOG(LogTemp, Warning, TEXT("Cloud connection initialized"));
}

void UCloudSaveManager::StartAutoSync()
{
	if (!bEnableAutoSync || !GetWorld())
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(
		AutoSyncTimerHandle,
		this,
		&UCloudSaveManager::SyncWithCloud,
		AutoSyncInterval,
		true
	);

	UE_LOG(LogTemp, Warning, TEXT("Auto-sync started with interval: %.1f seconds"), AutoSyncInterval);
}

void UCloudSaveManager::StopAutoSync()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(AutoSyncTimerHandle);
		UE_LOG(LogTemp, Warning, TEXT("Auto-sync stopped"));
	}
}
