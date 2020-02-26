extends HBoxContainer
class_name ControlRodPanel

var controlRod: ControlRod
var indicatorLights := []


func _ready():
	indicatorLights.append($LightsContainer/IndicatorLight0)
	indicatorLights.append($LightsContainer/IndicatorLight1)
	indicatorLights.append($LightsContainer/IndicatorLight2)
	indicatorLights.append($LightsContainer/IndicatorLight3)


func _process(delta):
	var p := controlRod.percent_out() as float
	
	if p == 1.0:
		turn_lights_on(0)
	elif p > 0.75:
		#print("75")
		turn_lights_on(1)
	elif p > 0.50:
		#print("50")
		turn_lights_on(2)
	elif p > 0.0:
		#print("25")
		turn_lights_on(3)
	else:
		turn_lights_on(4)


func _physics_process(delta):
	if $HBoxContainer/UpButton.is_pressed:
		controlRod.move_up(delta)
	elif $HBoxContainer/DownButton.is_pressed:
		controlRod.move_down(delta)


func turn_lights_on(n: int):
	for ii in range(0, indicatorLights.size()):
		indicatorLights[ii].set_on(n > 0 && (ii+1 <= n || ii+1 == n))
