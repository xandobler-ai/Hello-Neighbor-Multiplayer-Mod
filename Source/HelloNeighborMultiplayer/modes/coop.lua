-- Co-operative Game Mode
-- Players work together to complete objectives

local coop_mode = {}

function coop_mode.init()
    print("[CoOp Mode] Initializing cooperative gameplay...")
    coop_mode.objectives = {}
    coop_mode.completed_count = 0
    coop_mode.max_objectives = 5
    coop_mode.shared_timer = 0
end

function coop_mode.add_objective(objective_name, objective_description)
    table.insert(coop_mode.objectives, {
        name = objective_name,
        description = objective_description,
        completed = false
    })
    print("[CoOp Mode] Added objective: " .. objective_name)
end

function coop_mode.complete_objective(objective_id)
    if coop_mode.objectives[objective_id] then
        coop_mode.objectives[objective_id].completed = true
        coop_mode.completed_count = coop_mode.completed_count + 1
        print("[CoOp Mode] Objective completed: " .. coop_mode.objectives[objective_id].name)
        
        if coop_mode.completed_count == coop_mode.max_objectives then
            print("[CoOp Mode] All objectives completed! Team victory!")
            return true  -- Victory
        end
    end
    return false
end

function coop_mode.get_progress()
    return coop_mode.completed_count / coop_mode.max_objectives
end

function coop_mode.broadcast_message(message)
    print("[CoOp Mode] Team Message: " .. message)
end

return coop_mode
