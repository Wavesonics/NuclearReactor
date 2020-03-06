extends Node

var scram: bool = false
var controlRods := []


func _process(delta):
	if Engine.is_editor_hint():
		return
	
	var changed := false
	
	if Input.is_action_just_released("scram"):
		print("SCRAM!")
		scram = true
	
	var allIn := true
	for rod in controlRods:
		if scram:
			rod.move_in(delta, rod.scramSpeed)
			if rod.percent_out() > 0.0:
				allIn = false
	"""
		else:
			if Input.is_action_pressed("ui_up"):
				rod.move_out(delta, rod.speed)
			elif Input.is_action_pressed("ui_down"):
				rod.move_in(delta, rod.speed)
	"""
	
	if allIn and scram:
		scram = false


func add_control_rod(rod):
	controlRods.push_back(rod);
