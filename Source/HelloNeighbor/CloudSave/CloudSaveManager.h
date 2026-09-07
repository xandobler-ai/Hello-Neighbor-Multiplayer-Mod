#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CloudSaveManager.generated.h"

/**
 * Cloud save data structure for cross-platform progress
 */
USTRUCT(BlueprintType)
struct FCloudSaveData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Cloud Save")
	FString PlayerId;

	UPROPERTY(BlueprintReadWrite, Category = "Cloud Save")
	int32 CurrentLevel;

	UPROPERTY(BlueprintReadWrite, Category = "Cloud Save")
	float CurrentScore;

	UPROPERTY(BlueprintReadWrite, Category = "Cloud Save")
	int32 TotalPlayTime; // in seconds

	UPROPERTY(BlueprintReadWrite, Category = "Cloud Save")
	FString LastPlatform;

	UPROPERTY(BlueprintReadWrite, Category = "Cloud Save")
	FDateTime LastSaveTime;

	UPROPERTY(BlueprintReadWrite, Category = "Cloud Save")
	TArray<FString> UnlockedItems;

	UPROPERTY(BlueprintReadWrite, Category = "Cloud Save")
	TMap<FString, float> PlayerStats;
};

/**
 * Cross-platform cloud save system
 */
UCLASS()
class HELLONEIGHBOR_API UCloudSaveManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// Save operations
	UFUNCTION(BlueprintCallable, Category = "Cloud Save")
	void SaveGameToCloud(const FCloudSaveData& SaveData);

	UFUNCTION(BlueprintCallable, Category = "Cloud Save")
	void LoadGameFromCloud(const FString& PlayerId);

	// Synchronization
	UFUNCTION(BlueprintCallable, Category = "Cloud Save")
	void SyncWithCloud();

	UFUNCTION(BlueprintCallable, Category = "Cloud Save")
	void MergeCloudData(const FCloudSaveData& LocalData, const FCloudSaveData& CloudData);

	// Backup and recovery
	UFUNCTION(BlueprintCallable, Category = "Cloud Save")
	void BackupLocalSave(const FString& PlayerId);

	UFUNCTION(BlueprintCallable, Category = "Cloud Save")
	void RestoreFromBackup(const FString& PlayerId);

	// Delegates
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two(FOnCloudSaveComplete, bool, bSuccess, const FString&, Message);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two(FOnCloudLoadComplete, bool, bSuccess, const FCloudSaveData&, SaveData);

	UPROPERTY(BlueprintAssignable, Category = "Cloud Save")
	FOnCloudSaveComplete OnCloudSaveComplete;

	UPROPERTY(BlueprintAssignable, Category = "Cloud Save")
	FOnCloudLoadComplete OnCloudLoadComplete;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cloud Save")
	FCloudSaveData CurrentSaveData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cloud Save")
	bool bEnableAutoSync;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cloud Save")
	float AutoSyncInterval; // in seconds

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cloud Save")
	FString CloudStoragePath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cloud Save")
	FString LocalStoragePath;

private:
	void InitializeCloudConnection();
	void StartAutoSync();
	void StopAutoSync();

	FTimerHandle AutoSyncTimerHandle;
	bool bCloudConnected;
};
