-- Configuration for Hello Neighbor Multiplayer Mod

local config = {
    -- Co-op Mode Settings
    coop = {
        max_players = 4,
        objective_count = 5,
        time_limit = 600,  -- 10 minutes in seconds
        shared_resources = true
    },
    
    -- Versus Mode Settings
    versus = {
        max_players = 4,
        match_duration = 600,  -- 10 minutes
        target_score = 1000,
        score_mode = false  -- false = time-based, true = score-based
    },
    
    -- Network Settings
    network = {
        enable_voice_chat = true,
        enable_text_chat = true,
        max_ping = 250,
        tick_rate = 60
    },
    
    -- Gameplay Settings
    gameplay = {
        enable_damage = true,
        player_health = 100,
        enable_respawn = true,
        respawn_delay = 5  -- seconds
    }
}

return config
