# Installation Instructions

## Hello Neighbor Multiplayer Mod

### Requirements
- Hello Neighbor (Steam)
- UE4SS (Unreal Engine 4 Script System)
- Lua support enabled

### Installation Steps

1. **Download the Mod**
   - Download the latest release from GitHub
   - Extract the ZIP file

2. **Locate Your Mods Folder**
   - Windows Steam path:
     ```
     C:\Program Files (x86)\Steam\steamapps\common\Hello Neighbor\Mods\
     ```

3. **Install the Mod**
   - Copy the extracted `HelloNeighborMultiplayer` folder into your Mods directory
   - The folder structure should look like:
     ```
     C:\Program Files (x86)\Steam\steamapps\common\Hello Neighbor\Mods\
     └── HelloNeighborMultiplayer/
         ├── main.lua
         ├── config.lua
         ├── modes/
         │   ├── coop.lua
         │   └── versus.lua
         ├── network/
         │   └── replication.lua
         ├── ui/
         │   └── mode_selector.lua
         └── mod.json
     ```

4. **Enable the Mod**
   - Launch Hello Neighbor
   - The mod should be automatically detected
   - Enable it in the mod menu if needed

5. **Start Playing**
   - Create a new act
   - Select your preferred mode: Co-op or Versus
   - Invite friends to play

### Troubleshooting

**Mod Not Loading?**
- Verify the folder structure matches the format above
- Check that mod.json is present in the HelloNeighborMultiplayer folder
- Ensure main.lua exists in the HelloNeighborMultiplayer folder
- Check the game's mod logs for errors
- Verify UE4SS is properly installed and configured

**Performance Issues?**
- Reduce tick_rate in config.lua (default: 60)
- Lower max_players setting (default: 4)
- Disable voice chat if experiencing lag

**Multiplayer Connection Problems?**
- Ensure both players have the mod installed
- Check firewall settings
- Verify network connectivity
- Try increasing max_ping value in config.lua (default: 250ms)

### Uninstallation

To remove the mod:
1. Navigate to: `C:\Program Files (x86)\Steam\steamapps\common\Hello Neighbor\Mods\`
2. Delete the `HelloNeighborMultiplayer` folder
3. Restart the game

### Support

For issues or questions:
- Check the README.md file
- Visit: https://github.com/xandobler-ai/Hello-Neighbor-Multiplayer-Mod
- Open an issue on GitHub
