#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformManager.generated.h"

/**
 * Platform enumeration for cross-platform support
 */
UENUM(BlueprintType)
enum class EPlatformType : uint8
{
	PC_Windows = 0,
	PC_Mac = 1,
	PC_Linux = 2,
	Console_PS5 = 3,
	Console_Xbox = 4,
	Mobile_iOS = 5,
	Mobile_Android = 6,
	Unknown = 7
};

/**
 * Device capability flags
 */
UENUM(BlueprintType)
enum class EDeviceCapability : uint8
{
	TouchScreen = 0,
	Gamepad = 1,
	Keyboard = 2,
	Mouse = 3,
	Haptics = 4,
	MotionControls = 5
};

/**
 * Cross-platform manager handling all platform-specific logic
 */
UCLASS()
class HELLONEIGHBOR_API APlatformManager : public AActor
{
	GENERATED_BODY()

public:
	APlatformManager();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Platform detection
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Platform")
	EPlatformType GetCurrentPlatform() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Platform")
	FString GetPlatformName() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Platform")
	bool IsMobilePlatform() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Platform")
	bool IsConsolePlatform() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Platform")
	bool IsPCPlatform() const;

	// Device capabilities
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Platform")
	bool HasDeviceCapability(EDeviceCapability Capability) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Platform")
	float GetScreenDensity() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Platform")
	FVector2D GetScreenResolution() const;

	// Platform-specific initialization
	UFUNCTION(BlueprintCallable, Category = "Platform")
	void InitializePlatformServices();

	UFUNCTION(BlueprintCallable, Category = "Platform")
	void ShutdownPlatformServices();

	// Input management
	UFUNCTION(BlueprintCallable, Category = "Platform")
	void SetupPlatformInput();

	// Graphics optimization
	UFUNCTION(BlueprintCallable, Category = "Platform")
	void ApplyPlatformGraphicsSettings();

	// Network optimization
	UFUNCTION(BlueprintCallable, Category = "Platform")
	void OptimizeNetworkForPlatform();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform")
	EPlatformType CurrentPlatform;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform")
	TArray<EDeviceCapability> AvailableCapabilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Network")
	int32 MaxNetworkPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Graphics")
	bool bEnableRayTracing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Graphics")
	float GraphicsQualityScale;

private:
	void DetectPlatform();
	void DetectDeviceCapabilities();
	void InitializeWindowsPlatform();
	void InitializeMacPlatform();
	void InitializeLinuxPlatform();
	void InitializePS5Platform();
	void InitializeXboxPlatform();
	void InitializeIOSPlatform();
	void InitializeAndroidPlatform();

	FVector2D ScreenResolution;
	float ScreenDensity;
};
