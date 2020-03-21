extends Node2D

onready var pipes := get_tree().get_nodes_in_group("pipes")
onready var pipeJoints := get_tree().get_nodes_in_group("pipe_joints")
onready var sensors := get_tree().get_nodes_in_group("sensors")
const TASK_TAG := "fluid_worker"


func _ready():
	set_process_input(true)
	
	$ReactorCore/NeutronField.init_bsp_tree()
	
	if OS.has_feature("vr"):
		$ReactorCore/NeutronField.enableRendering = false
		$BiproductMap.enableRendering = false
		$ThermalMap.enableRendering = false
		
		var thermocouples := get_tree().get_nodes_in_group("thermocouples")
		for thermocouple in thermocouples:
			thermocouple.enableRendering = false
		
		for pipe in pipes:
			pipe.enableRendering = false
		
		for join in pipeJoints:
			join.enableRendering = false
		
		for sensor in sensors:
			sensor.enableRendering = false

"""
func _input(event):
	if event is InputEventMouseButton:
		if event.button_index == BUTTON_LEFT and event.pressed:
			
			var pos := event.global_position as Vector2
			print("Add heat to " + String(pos))
			$ReactorCore/NeutronField.add_heat(pos, 1000.0)
"""

func _on_CoolantLoopSimulationTimer_timeout():
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
	
	# These need to happen after all normal pipes
	for joint in pipeJoints:
		joint.fluid_tick()
	
	# Now back on the main thread, finish up
	# Update each pipe from the pipe behind it
	for pipe in pipes:
		pipe.update_from_prev()
		pipe.update()


func _on_BiproductMapUpdateTimer_timeout():
	$BiproductMap.update()
