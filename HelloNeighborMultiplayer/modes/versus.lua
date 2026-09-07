-- Competitive/Versus Game Mode
-- Players compete against each other

local versus_mode = {}

function versus_mode.init()
    print("[Versus Mode] Initializing competitive gameplay...")
    versus_mode.players = {}
    versus_mode.match_active = false
    versus_mode.match_timer = 0
    versus_mode.max_time = 600  -- 10 minutes
end

function versus_mode.add_player(player_id, player_name)
    table.insert(versus_mode.players, {
        id = player_id,
        name = player_name,
        score = 0,
        kills = 0,
        deaths = 0
    })
    print("[Versus Mode] Player joined: " .. player_name)
end

function versus_mode.award_points(player_id, points)
    for _, player in ipairs(versus_mode.players) do
        if player.id == player_id then
            player.score = player.score + points
            print("[Versus Mode] " .. player.name .. " awarded " .. points .. " points (Total: " .. player.score .. ")")
            break
        end
    end
end

function versus_mode.record_kill(player_id)
    for _, player in ipairs(versus_mode.players) do
        if player.id == player_id then
            player.kills = player.kills + 1
            break
        end
    end
end

function versus_mode.record_death(player_id)
    for _, player in ipairs(versus_mode.players) do
        if player.id == player_id then
            player.deaths = player.deaths + 1
            break
        end
    end
end

function versus_mode.get_leaderboard()
    local leaderboard = {}
    for _, player in ipairs(versus_mode.players) do
        table.insert(leaderboard, {
            name = player.name,
            score = player.score,
            kills = player.kills,
            deaths = player.deaths
        })
    end
    
    -- Sort by score (descending)
    table.sort(leaderboard, function(a, b) return a.score > b.score end)
    
    return leaderboard
end

function versus_mode.get_leading_player()
    if #versus_mode.players > 0 then
        local leader = versus_mode.players[1]
        for _, player in ipairs(versus_mode.players) do
            if player.score > leader.score then
                leader = player
            end
        end
        return leader
    end
    return nil
end

return versus_mode
