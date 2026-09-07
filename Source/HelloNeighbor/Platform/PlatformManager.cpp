#include "Platform/PlatformManager.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Misc/ConfigCacheIni.h"

APlatformManager::APlatformManager()
	: CurrentPlatform(EPlatformType::Unknown)
	, MaxNetworkPlayers(8)
	, bEnableRayTracing(false)
	, GraphicsQualityScale(1.0f)
	, ScreenDensity(1.0f)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f;
}

void APlatformManager::BeginPlay()
{
	Super::BeginPlay();

	DetectPlatform();
	DetectDeviceCapabilities();
	InitializePlatformServices();
	SetupPlatformInput();
	ApplyPlatformGraphicsSettings();
	OptimizeNetworkForPlatform();

	UE_LOG(LogTemp, Warning, TEXT("PlatformManager initialized for: %s"), *GetPlatformName());
}

void APlatformManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

EPlatformType APlatformManager::GetCurrentPlatform() const
{
	return CurrentPlatform;
}

FString APlatformManager::GetPlatformName() const
{
	switch (CurrentPlatform)
	{
		case EPlatformType::PC_Windows: return TEXT("Windows PC");
		case EPlatformType::PC_Mac: return TEXT("Mac");
		case EPlatformType::PC_Linux: return TEXT("Linux");
		case EPlatformType::Console_PS5: return TEXT("PlayStation 5");
		case EPlatformType::Console_Xbox: return TEXT("Xbox Series X/S");
		case EPlatformType::Mobile_iOS: return TEXT("iOS");
		case EPlatformType::Mobile_Android: return TEXT("Android");
		default: return TEXT("Unknown");
	}
}

bool APlatformManager::IsMobilePlatform() const
{
	return CurrentPlatform == EPlatformType::Mobile_iOS || CurrentPlatform == EPlatformType::Mobile_Android;
}

bool APlatformManager::IsConsolePlatform() const
{
	return CurrentPlatform == EPlatformType::Console_PS5 || CurrentPlatform == EPlatformType::Console_Xbox;
}

bool APlatformManager::IsPCPlatform() const
{
	return CurrentPlatform == EPlatformType::PC_Windows || 
		   CurrentPlatform == EPlatformType::PC_Mac || 
		   CurrentPlatform == EPlatformType::PC_Linux;
}

bool APlatformManager::HasDeviceCapability(EDeviceCapability Capability) const
{
	return AvailableCapabilities.Contains(Capability);
}

float APlatformManager::GetScreenDensity() const
{
	return ScreenDensity;
}

FVector2D APlatformManager::GetScreenResolution() const
{
	return ScreenResolution;
}

void APlatformManager::InitializePlatformServices()
{
	switch (CurrentPlatform)
	{
		case EPlatformType::PC_Windows:
			InitializeWindowsPlatform();
			break;
		case EPlatformType::PC_Mac:
			InitializeMacPlatform();
			break;
		case EPlatformType::PC_Linux:
			InitializeLinuxPlatform();
			break;
		case EPlatformType::Console_PS5:
			InitializePS5Platform();
			break;
		case EPlatformType::Console_Xbox:
			InitializeXboxPlatform();
			break;
		case EPlatformType::Mobile_iOS:
			InitializeIOSPlatform();
			break;
		case EPlatformType::Mobile_Android:
			InitializeAndroidPlatform();
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Unknown platform for initialization"));
	}
}

void APlatformManager::ShutdownPlatformServices()
{
	UE_LOG(LogTemp, Warning, TEXT("Shutting down platform services for: %s"), *GetPlatformName());
}

void APlatformManager::SetupPlatformInput()
{
	// Platform-specific input setup handled by PlatformInputManager
	UE_LOG(LogTemp, Warning, TEXT("Platform input setup completed for: %s"), *GetPlatformName());
}

void APlatformManager::ApplyPlatformGraphicsSettings()
{
	// Platform-specific graphics settings handled by PlatformGraphicsSettings
	UE_LOG(LogTemp, Warning, TEXT("Applied graphics settings for: %s"), *GetPlatformName());
}

void APlatformManager::OptimizeNetworkForPlatform()
{
	// Adjust network settings based on platform capabilities
	if (IsMobilePlatform())
	{
		// Reduce update frequency for mobile
		MaxNetworkPlayers = 4;
	}
	else if (IsConsolePlatform())
	{
		// Optimize for console bandwidth
		MaxNetworkPlayers = 8;
	}
	else
	{
		// PC can handle more players
		MaxNetworkPlayers = 16;
	}

	UE_LOG(LogTemp, Warning, TEXT("Network optimized for %s - Max players: %d"), 
		*GetPlatformName(), MaxNetworkPlayers);
}

void APlatformManager::DetectPlatform()
{
#if PLATFORM_WINDOWS
	CurrentPlatform = EPlatformType::PC_Windows;
#elif PLATFORM_MAC
	CurrentPlatform = EPlatformType::PC_Mac;
#elif PLATFORM_LINUX
	CurrentPlatform = EPlatformType::PC_Linux;
#elif PLATFORM_PS5
	CurrentPlatform = EPlatformType::Console_PS5;
#elif PLATFORM_XBOXSX
	CurrentPlatform = EPlatformType::Console_Xbox;
#elif PLATFORM_IOS
	CurrentPlatform = EPlatformType::Mobile_iOS;
#elif PLATFORM_ANDROID
	CurrentPlatform = EPlatformType::Mobile_Android;
#else
	CurrentPlatform = EPlatformType::Unknown;
#endif

	// Get screen resolution
	FDisplayMetrics DisplayMetrics;
	FSlateApplication::Get().GetDisplayMetrics(DisplayMetrics);
	ScreenResolution = FVector2D(DisplayMetrics.PrimaryDisplayWidth, DisplayMetrics.PrimaryDisplayHeight);
	
	UE_LOG(LogTemp, Warning, TEXT("Platform detected: %s - Resolution: %fx%f"), 
		*GetPlatformName(), ScreenResolution.X, ScreenResolution.Y);
}

void APlatformManager::DetectDeviceCapabilities()
{
	AvailableCapabilities.Empty();

	// All platforms support gamepad
	AvailableCapabilities.Add(EDeviceCapability::Gamepad);

	if (IsPCPlatform())
	{
		AvailableCapabilities.Add(EDeviceCapability::Keyboard);
		AvailableCapabilities.Add(EDeviceCapability::Mouse);
		bEnableRayTracing = true;
	}
	else if (IsConsolePlatform())
	{
		AvailableCapabilities.Add(EDeviceCapability::Haptics);
		AvailableCapabilities.Add(EDeviceCapability::MotionControls);
	}
	else if (IsMobilePlatform())
	{
		AvailableCapabilities.Add(EDeviceCapability::TouchScreen);
		AvailableCapabilities.Add(EDeviceCapability::Haptics);
		AvailableCapabilities.Add(EDeviceCapability::MotionControls);
	}

	UE_LOG(LogTemp, Warning, TEXT("Device capabilities detected for %s"), *GetPlatformName());
}

void APlatformManager::InitializeWindowsPlatform()
{
	GraphicsQualityScale = 1.0f;
	bEnableRayTracing = true;
	UE_LOG(LogTemp, Warning, TEXT("Windows PC platform initialized"));
}

void APlatformManager::InitializeMacPlatform()
{
	GraphicsQualityScale = 0.9f;
	bEnableRayTracing = false;
	UE_LOG(LogTemp, Warning, TEXT("Mac platform initialized"));
}

void APlatformManager::InitializeLinuxPlatform()
{
	GraphicsQualityScale = 0.85f;
	bEnableRayTracing = false;
	UE_LOG(LogTemp, Warning, TEXT("Linux platform initialized"));
}

void APlatformManager::InitializePS5Platform()
{
	GraphicsQualityScale = 1.0f;
	bEnableRayTracing = true;
	UE_LOG(LogTemp, Warning, TEXT("PlayStation 5 platform initialized"));
}

void APlatformManager::InitializeXboxPlatform()
{
	GraphicsQualityScale = 1.0f;
	bEnableRayTracing = true;
	UE_LOG(LogTemp, Warning, TEXT("Xbox Series X/S platform initialized"));
}

void APlatformManager::InitializeIOSPlatform()
{
	GraphicsQualityScale = 0.5f;
	bEnableRayTracing = false;
	UE_LOG(LogTemp, Warning, TEXT("iOS platform initialized"));
}

void APlatformManager::InitializeAndroidPlatform()
{
	GraphicsQualityScale = 0.6f;
	bEnableRayTracing = false;
	UE_LOG(LogTemp, Warning, TEXT("Android platform initialized"));
}
