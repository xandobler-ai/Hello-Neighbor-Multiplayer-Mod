#include "HelloNeighborMultiplayer.h"

#define LOCTEXT_NAMESPACE "FHelloNeighborMultiplayerModule"

void FHelloNeighborMultiplayerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory
	// The exact timing is specified in the .uplugin file's LoadingPhase
	UE_LOG(LogTemp, Warning, TEXT("HelloNeighborMultiplayer module loaded successfully"));
}

void FHelloNeighborMultiplayerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module
	UE_LOG(LogTemp, Warning, TEXT("HelloNeighborMultiplayer module unloaded"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FHelloNeighborMultiplayerModule, HelloNeighborMultiplayer)
