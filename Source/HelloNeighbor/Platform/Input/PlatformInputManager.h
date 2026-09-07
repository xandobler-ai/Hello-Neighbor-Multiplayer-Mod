#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Platform/PlatformManager.h"
#include "PlatformInputManager.generated.h"

class UEnhancedInputComponent;
class UEnhancedInputSubsystem;

/**
 * Input device type enumeration
 */
UENUM(BlueprintType)
enum class EInputDeviceType : uint8
{
	KeyboardMouse = 0,
	Gamepad = 1,
	TouchScreen = 2,
	Unknown = 3
};

/**
 * Cross-platform input manager handling all input types
 */
UCLASS()
class HELLONEIGHBOR_API APlatformInputManager : public APlayerController
{
	GENERATED_BODY()

public:
	APlatformInputManager();

	virtual void BeginPlay() override;
	virtual void SetupInput(class UInputComponent* PlayerInputComponent) override;

	// Input device detection
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Input")
	EInputDeviceType GetCurrentInputDevice() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Input")
	FString GetInputDeviceName() const;

	// Haptic feedback (console and mobile)
	UFUNCTION(BlueprintCallable, Category = "Input")
	void PlayHapticFeedback(float Intensity = 1.0f, float Duration = 0.1f);

	// Touch input support (mobile)
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetupTouchInput();

	// Gamepad input support (all platforms)
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetupGamepadInput();

	// Keyboard/Mouse input support (PC)
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetupKeyboardMouseInput();

	// Motion controls (console and mobile)
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetupMotionControls();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	EInputDeviceType CurrentInputDevice;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	APlatformManager* PlatformManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float TouchSensitivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float GamepadSensitivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float HapticIntensity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bEnableMotionControls;

private:
	void DetectInputDevice();
	void InitializeInputDevice();

	class UEnhancedInputComponent* EnhancedInputComponent;
	class UEnhancedInputSubsystem* EnhancedInputSubsystem;
};
