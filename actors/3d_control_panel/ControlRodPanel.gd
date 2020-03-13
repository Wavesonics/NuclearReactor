extends Spatial

var controlRodNumber: int
var controlRod = null
var numLights: int


func _ready():
	numLights = $IndicatorLights.get_child_count()


func set_control_rod(rod, number):
	self.controlRod = rod
	self.controlRodNumber = number
	$ControlRodLabel.text = "Control Rod %d" % controlRodNumber


func _process(delta):
	var p := controlRod.percent_out() as float
	var s := 1.0 / numLights
	var x = (p/s) as int
	turn_lights_on((numLights-x)+1)


func _physics_process(delta):
	if $OutButton.triggering:
		controlRod.move_out(delta, controlRod.speed)
	elif $InButton.triggering:
		controlRod.move_in(delta, controlRod.speed)


func turn_lights_on(n: int):
	for ii in range(0, numLights):
		$IndicatorLights.get_child(ii).set_on(n > 0 && ii+1 < n)
