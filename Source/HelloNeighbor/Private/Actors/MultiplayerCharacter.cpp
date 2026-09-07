#include "Actors/MultiplayerCharacter.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputActionValue.h"

AMultiplayerCharacter::AMultiplayerCharacter()
{
    PrimaryActorTick.TickInterval = 0.0f;
    PrimaryActorTick.TickType = ETickableTickType::Always;

    bReplicates = true;
    bReplicateMovement = true;

    PlayerIndex = -1;
    PlayerName = TEXT("Player");
    bIsAlive = true;
    MaxHealth = 100.0f;
    Health = MaxHealth;
}

void AMultiplayerCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AMultiplayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (IsLocallyControlled())
    {
        ReplicateMovement();
    }
}

void AMultiplayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (PlayerInputComponent)
    {
        // Movement
        PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMultiplayerCharacter::MoveForward);
        PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMultiplayerCharacter::MoveRight);
        PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMultiplayerCharacter::LookUp);
        PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMultiplayerCharacter::TurnRight);
    }
}

void AMultiplayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AMultiplayerCharacter, PlayerIndex);
    DOREPLIFETIME(AMultiplayerCharacter, PlayerName);
    DOREPLIFETIME(AMultiplayerCharacter, ReplicatedLocation);
    DOREPLIFETIME(AMultiplayerCharacter, ReplicatedRotation);
    DOREPLIFETIME(AMultiplayerCharacter, bIsAlive);
    DOREPLIFETIME(AMultiplayerCharacter, Health);
}

void AMultiplayerCharacter::SetPlayerName(const FString& NewName)
{
    if (HasAuthority())
    {
        PlayerName = NewName;
        UE_LOG(LogTemp, Warning, TEXT("Player Name Set: %s"), *PlayerName);
    }
}

void AMultiplayerCharacter::TakeDamage(float DamageAmount)
{
    if (HasAuthority() && bIsAlive)
    {
        Health -= DamageAmount;
        if (Health <= 0.0f)
        {
            Health = 0.0f;
            bIsAlive = false;
            UE_LOG(LogTemp, Warning, TEXT("%s has died"), *PlayerName);
        }
    }
}

void AMultiplayerCharacter::Heal(float HealAmount)
{
    if (HasAuthority() && bIsAlive)
    {
        Health = FMath::Min(Health + HealAmount, MaxHealth);
    }
}

void AMultiplayerCharacter::Respawn()
{
    if (HasAuthority())
    {
        bIsAlive = true;
        Health = MaxHealth;
        UE_LOG(LogTemp, Warning, TEXT("%s has respawned"), *PlayerName);
    }
}

void AMultiplayerCharacter::MoveForward(float Value)
{
    if (IsAlive() && Controller)
    {
        MovementInput.X = Value;
        AddMovementInput(GetActorForwardVector(), Value);
    }
}

void AMultiplayerCharacter::MoveRight(float Value)
{
    if (IsAlive() && Controller)
    {
        MovementInput.Y = Value;
        AddMovementInput(GetActorRightVector(), Value);
    }
}

void AMultiplayerCharacter::LookUp(float Value)
{
    if (IsAlive() && Controller)
    {
        LookInput.Pitch = Value;
        AddControllerPitchInput(Value);
    }
}

void AMultiplayerCharacter::TurnRight(float Value)
{
    if (IsAlive() && Controller)
    {
        LookInput.Yaw = Value;
        AddControllerYawInput(Value);
    }
}

void AMultiplayerCharacter::ReplicateMovement()
{
    ReplicatedLocation = GetActorLocation();
    ReplicatedRotation = GetActorRotation();
}
