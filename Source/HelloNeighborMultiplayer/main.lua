-- Hello Neighbor Multiplayer Mod Main Script
-- Co-op and Versus game modes

local mod_version = "1.0.0"
local mod_name = "HelloNeighborMultiplayer"

print("[" .. mod_name .. "] Initializing Multiplayer Mod v" .. mod_version)

-- Initialize multiplayer systems
function init_multiplayer()
    print("[" .. mod_name .. "] Setting up multiplayer systems...")
    
    -- Register game modes
    register_game_mode("CoOp", "Cooperative Gameplay")
    register_game_mode("Versus", "Competitive Gameplay")
    
    print("[" .. mod_name .. "] Multiplayer systems initialized!")
end

-- Register a game mode
function register_game_mode(mode_name, mode_description)
    print("[" .. mod_name .. "] Registered game mode: " .. mode_name .. " - " .. mode_description)
end

-- Initialize on load
init_multiplayer()

print("[" .. mod_name .. "] Mod loaded successfully!")
