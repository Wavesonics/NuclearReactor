extends HBoxContainer
class_name ControlRodPanel

var lightScene := preload("res://actors/2d_control_panel/IndicatorLight.tscn")

var controlRod: ControlRod
var numLights := 10


func _ready():
	for ii in range(0, numLights):
		var node := lightScene.instance()
		$LightsContainer.add_child(node)


func _process(delta):
	var p := controlRod.percent_out() as float
	var s := 1.0 / numLights
	var x = (p/s) as int
	turn_lights_on((numLights-x)+1)


func _physics_process(delta):
	if $HBoxContainer/UpButton.is_pressed:
		controlRod.move_up(delta)
	elif $HBoxContainer/DownButton.is_pressed:
		controlRod.move_down(delta)


func turn_lights_on(n: int):
	for ii in range(0, numLights):
		$LightsContainer.get_child(ii).set_on(n > 0 && ii+1 < n)
