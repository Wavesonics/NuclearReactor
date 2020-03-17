extends Node2D

#onready var pipes := get_tree().get_nodes_in_group("pipes")
var pipes := []

func _ready():
	pipes.push_back($Pipe0)
	pipes.push_back($Pipe1)
	pipes.push_back($Pipe2)
	pipes.push_back($Pipe3)


func _process(delta):
	if Input.is_action_just_released("scram"): # Just for debugging
		tick_fluid_sim()


func tick_fluid_sim():
	for pipe in pipes:
		pipe.fluid_tick()
	
	for pipe in pipes:
		pipe.update_from_prev()
		pipe.update()


func _on_FluidSimTimer_timeout():
	tick_fluid_sim()
	pass
