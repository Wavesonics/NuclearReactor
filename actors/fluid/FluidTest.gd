extends Node2D

onready var pipes := get_tree().get_nodes_in_group("pipes")
onready var pipeJoints := get_tree().get_nodes_in_group("pipe_joints")

const TASK_TAG := "fluid_worker"
var tasksFinished := 0


func _ready():
	set_process_input(true)


func _input(event):
	if event is InputEventMouseButton:
		if event.button_index == 1 and event.is_pressed():
			for pipe in pipes:
				if pipe.contains_point(event.global_position):
					var p = pipe.get_pressure(event.global_position)
					pipe.set_pressure_by_position(event.global_position, pipe.maxPressure)


func tick_fluid_sim():
	var tasks := []
	# Process each pipe individually
	for pipe in pipes:
		var task = GlobalThreadPool.submit_task_unparameterized(pipe, "fluid_tick", TASK_TAG)
		tasks.push_back(task)
	
	# Wait for all pipes to finish
	for task in tasks:
		var result = task.wait_for_result()
	
	# These need to happen after all normal pipes
	for joint in pipeJoints:
		joint.fluid_tick()
	
	# Now back on the main thread, finish up
	# Update each pipe from the pipe behind it
	for pipe in pipes:
		pipe.update_from_prev()
		pipe.update()


func _on_FluidSimTimer_timeout():
	tick_fluid_sim()
