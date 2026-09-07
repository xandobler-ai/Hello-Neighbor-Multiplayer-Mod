# Hello Neighbor Multiplayer Mod

A multiplayer modification for Hello Neighbor that enables cooperative and competitive gameplay using Unreal Engine.

## Features

- **Game Mode Selection**: Choose between Co-op or Versus modes
- **Co-op Mode**: Work together to complete objectives and escape the neighbor's house
- **Versus Mode**: Compete against other players in various challenges
- **Multiplayer Synchronization**: Real-time player state and action synchronization
- **Network Architecture**: Built on Unreal's replication system

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
│   │   └── GameState.h/.cpp
│   ├── UI/
│   │   ├── ModeSelectionWidget.h/.cpp
│   │   ├── PlayerHUD.h/.cpp
│   │   └── ObjectiveWidget.h/.cpp
│   └── HelloNeighbor.Build.cs
├── Plugins/
└── Content/
    └── Blueprints/
        ├── GameModes/
        ├── UI/
        └── Characters/
```

## Requirements

- Unreal Engine 4.27+ or Unreal Engine 5.x
- Visual Studio 2019+ with C++ support
- Hello Neighbor game files
- Windows or compatible system

## Installation

1. Clone this repository into your `Plugins` folder
2. Open the Hello Neighbor project in Unreal Engine
3. Rebuild the solution
4. Enable the plugin in Edit > Plugins
5. Restart the editor

## Development Setup

### Prerequisites
- Unreal Engine installed
- C++ project setup for Hello Neighbor
- Basic understanding of Unreal's replication system

### Building

1. Generate Visual Studio project files
2. Open the .sln in Visual Studio
3. Build the project
4. Open in Unreal Editor

## Usage

1. Start a multiplayer game
2. Select your preferred mode at the main menu:
   - **Co-op**: Collaborate with other players
   - **Versus**: Compete against others
3. Join an existing game or create a new session
4. Play!

## Architecture Overview

### Game Mode Selection System
- `HN_ModeSelector`: Widget-based mode selection interface
- Persistent game state across mode changes
- Smooth transitions between modes

### Character Replication
- Networked movement and animation
- Action synchronization
- Player state management

### Objective System
- Mode-specific objectives
- Progress tracking
- Completion callbacks

## Contributing

Contributions are welcome! Please:

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## License

MIT License - See LICENSE file for details

## Disclaimer

This is a fan-made modification for educational and entertainment purposes. Hello Neighbor is a trademark of tinyBuild. This mod is not affiliated with or endorsed by the original developers.

## Support

For issues, questions, or suggestions, please open an issue on the GitHub repository.
