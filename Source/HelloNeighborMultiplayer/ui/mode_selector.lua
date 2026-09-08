-- Mode Selection UI
-- Displays the menu for choosing between Co-op and Versus modes

local mode_selector = {}

function mode_selector.show_menu()
    print("\n" .. string.rep("=", 50))
    print("Hello Neighbor - Multiplayer Mod Mode Selection")
    print(string.rep("=", 50))
    print("1. Co-operative Mode")
    print("   - Work together with other players")
    print("   - Complete shared objectives")
    print("   - Up to 4 players")
    print("")
    print("2. Versus Mode")
    print("   - Compete against other players")
    print("   - Individual scoring system")
    print("   - Up to 4 players")
    print("")
    print("3. Exit")
    print(string.rep("=", 50))
end

function mode_selector.select_mode(choice)
    if choice == 1 then
        print("[UI] Starting Co-operative Mode...")
        return "coop"
    elseif choice == 2 then
        print("[UI] Starting Versus Mode...")
        return "versus"
    elseif choice == 3 then
        print("[UI] Exiting mod...")
        return "exit"
    else
        print("[UI] Invalid selection")
        return nil
    end
end

function mode_selector.show_player_hud(player_name)
    print("\n[HUD] Player: " .. player_name)
    print("[HUD] =====================================")
end

function mode_selector.update_objective_display(current, total)
    print("[HUD] Objectives: " .. current .. "/" .. total)
end

function mode_selector.update_score_display(score)
    print("[HUD] Score: " .. score)
end

return mode_selector
