extends Node2D

onready var pipes := get_tree().get_nodes_in_group("pipes")
const TASK_TAG := "fluid_worker"
var tasksFinished := 0


func _process(delta):
	if Input.is_action_just_released("scram"): # Just for debugging
		tick_fluid_sim()


func tick_fluid_sim():
	var tasks := []
	# Process each pipe individually
	for pipe in pipes:
		var task = GlobalThreadPool.submit_task_unparameterized(pipe, "fluid_tick", TASK_TAG)
		tasks.push_back(task)
	
	# Wait for all pipes to finish
	for task in tasks:
		var result = task.wait_for_result()
	
	# Now back on the main thread, finish up
	# Update each pipe from the pipe behind it
	for pipe in pipes:
		pipe.update_from_prev()
		pipe.update()


func _on_FluidSimTimer_timeout():
	tick_fluid_sim()
