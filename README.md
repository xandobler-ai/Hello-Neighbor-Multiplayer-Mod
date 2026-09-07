# Hello Neighbor Multiplayer Mod

A multiplayer modification for Hello Neighbor that enables cooperative and competitive gameplay using Unreal Engine with **full cross-platform support** (PC, Console, and Mobile).

## Features

- **Game Mode Selection**: Choose between Co-op or Versus modes
- **Co-op Mode**: Work together to complete objectives and escape the neighbor's house
- **Versus Mode**: Compete against other players in various challenges
- **Multiplayer Synchronization**: Real-time player state and action synchronization
- **Network Architecture**: Built on Unreal's replication system
- **🌍 Cross-Platform Support**: PC (Windows/Mac/Linux), Console (PS5/Xbox Series X), Mobile (iOS/Android)
- **Platform-Specific Input Handling**: Adaptive controls for keyboard, gamepad, and touch
- **Cloud Save Synchronization**: Cross-platform progress and settings persistence

## Supported Platforms

| Platform | Status | Input Method | Notes |
|----------|--------|--------------|-------|
| Windows PC | ✅ Supported | Keyboard & Mouse, Gamepad | Full performance |
| Mac | ✅ Supported | Keyboard & Mouse, Gamepad | Full performance |
| Linux | ✅ Supported | Keyboard & Mouse, Gamepad | Full performance |
| PlayStation 5 | ✅ Supported | DualSense Controller | Native haptics support |
| Xbox Series X/S | ✅ Supported | Xbox Controller | Optimized for performance |
| iOS | ✅ Supported | Touch, MFi Controller | Optimized for screen size |
| Android | ✅ Supported | Touch, Gamepad | Optimized for performance |

## Game Modes

### Co-op Mode
- Multiple players work together
- Shared objectives and puzzle solving
- Combined resources and tools
- Escape the house together

### Versus Mode
- Competitive gameplay
- Individual objectives
- Resource competition
- Score-based gameplay

## Project Structure

```
Source/
├── HelloNeighbor/
│   ├── Actors/
│   │   ├── MultiplayerCharacter.h/.cpp
│   │   └── GameModeManager.h/.cpp
│   ├── GameModes/
│   │   ├── HN_GameModeBase.h/.cpp
│   │   ├── HN_CoopGameMode.h/.cpp
│   │   ├── HN_VersusGameMode.h/.cpp
│   │   └── HN_ModeSelector.h/.cpp
│   ├── Network/
│   │   ├── PlayerState.h/.cpp
│   │   ├── GameState.h/.cpp
│   │   └── OnlineSessionManager.h/.cpp
│   ├── Platform/
│   │   ├── PlatformManager.h/.cpp
│   │   ├── Input/
│   │   │   ├── PlatformInputManager.h/.cpp
│   │   │   ├── MobileInputHandler.h/.cpp
│   │   │   ├── ConsoleInputHandler.h/.cpp
│   │   │   └── PCInputHandler.h/.cpp
│   │   └── Graphics/
│   │       ├── PlatformGraphicsSettings.h/.cpp
│   │       ├── MobileGraphicsOptimizer.h/.cpp
│   │       └── ConsoleGraphicsOptimizer.h/.cpp
│   ├── CloudSave/
│   │   ├── CloudSaveManager.h/.cpp
│   │   └── CrossPlatformProfileData.h/.cpp
│   ├── UI/
│   │   ├── ModeSelectionWidget.h/.cpp
│   │   ├── PlayerHUD.h/.cpp
│   │   ├── ObjectiveWidget.h/.cpp
│   │   └── PlatformAdaptiveUI.h/.cpp
│   └── HelloNeighbor.Build.cs
├── Plugins/
└── Content/
    └── Blueprints/
        ├── GameModes/
        ├── UI/
        ├── Characters/
        └── Platform/
            ├── MobileUI/
            ├── ConsoleUI/
            └── PCUI/
```

## Requirements

- Unreal Engine 4.27+ or Unreal Engine 5.x
- Visual Studio 2019+ with C++ support
- Hello Neighbor game files
- Platform-specific SDKs:
  - **PC**: Windows SDK, POSIX tools for Mac/Linux
  - **Console**: PlayStation SDK (PS5), Xbox SDK (Series X/S)
  - **Mobile**: Android SDK, iOS SDK

## Installation

1. Clone this repository into your `Plugins` folder
2. Open the Hello Neighbor project in Unreal Engine
3. Rebuild the solution
4. Enable the plugin in Edit > Plugins
5. Restart the editor
6. Configure platform-specific settings in Project Settings > HelloNeighbor > Cross-Platform

## Development Setup

### Prerequisites
- Unreal Engine installed
- C++ project setup for Hello Neighbor
- Basic understanding of Unreal's replication system
- Platform-specific developer accounts (PlayStation, Xbox for console support)

### Building

1. Generate Visual Studio project files
2. Open the .sln in Visual Studio
3. Build the project
4. Open in Unreal Editor

### Platform-Specific Build Instructions

#### Mobile (iOS)
```bash
# Build for iOS
./Engine/Build/BatchFiles/RunUAT.bat BuildCookRun -project=[Project].uproject -platform=IOS -configuration=Development
```

#### Mobile (Android)
```bash
# Build for Android
./Engine/Build/BatchFiles/RunUAT.bat BuildCookRun -project=[Project].uproject -platform=Android -configuration=Development
```

#### Console (PlayStation 5)
- Requires PS5 SDK
- Configure through Unreal Engine Platform Support
- Sign in with PlayStation Network credentials

#### Console (Xbox Series X/S)
- Requires Xbox SDK
- Configure through Unreal Engine Platform Support
- Sign in with Xbox Live account

## Usage

1. Start a multiplayer game
2. Select your preferred mode at the main menu:
   - **Co-op**: Collaborate with other players
   - **Versus**: Compete against others
3. Join an existing game or create a new session
4. Play! (Cross-platform matchmaking automatically available)

## Cross-Platform Features

### Input Adaptation
The mod automatically detects your platform and input device:
- **PC**: Supports keyboard/mouse, gamepad
- **Console**: Optimized for DualSense (PS5) or Xbox controller
- **Mobile**: Full touch controls with optional MFi gamepad support

### Graphics Optimization
Platform-specific graphics settings ensure optimal performance:
- **PC**: High-end graphics with ray-tracing options
- **Console**: Balanced performance and visual quality
- **Mobile**: Optimized for varying device capabilities

### Network Synchronization
Real-time cross-platform networking:
- Automatic platform detection
- Protocol optimization per platform
- Reduced latency for console and mobile

### Cloud Save System
Seamless progress across platforms:
- Automatic cloud backup
- Cross-platform profile synchronization
- Device-to-device progress transfer

## Contributing

Contributions are welcome! Please:

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly across multiple platforms
5. Submit a pull request

## License

MIT License - See LICENSE file for details

## Disclaimer

This is a fan-made modification for educational and entertainment purposes. Hello Neighbor is a trademark of tinyBuild. This mod is not affiliated with or endorsed by the original developers.

## Support

For issues, questions, or suggestions, please open an issue on the GitHub repository.
