extends Control


func random_direction() -> Vector2:
	var direction = Vector2(rand_range(0.0, 1.0), rand_range(0.0, 1.0)).normalized()
	if randi() % 2 ==1:
		direction.x *= -1
	if randi() % 2 == 1:
		direction.y *= -1
	return direction


func _ready():
	if OS.has_feature("vr"):
		$NeutronField.enableRendering = false
		$BiproductMap.enableRendering = false
		$ThermalMap.enableRendering = false

	#set_process_input(true)

	$MaxPopulationLabel.text = "Max neutron population: %d" % $NeutronField.get_max_population()
"""
	for ii in range(0,100000):
		var velocity = random_direction() * 10.0
		var position = Vector2(rand_range(50.0, 450.0), rand_range(50.0, 450.0))
		$NeutronField.createNeutron(position, velocity)
"""

"""
func _input(ev):
if Input.is_key_pressed(KEY_SPACE):
		$NeutronField.add_heat(Vector2(200.0, 200.0), 100.0)
		$ThermalMap.update()
		
func _input(event):
	if event is InputEventMouseButton:
		if event.button_index == BUTTON_LEFT and event.pressed:
			
			var pos := event.position as Vector2
			print("Add biproduct to " + String(pos))
			$NeutronField.addFissionBiproduct(pos)
"""

func _process(delta):
	$FpsLabel.text = "%d fps" % Engine.get_frames_per_second()
	
	var flux := $NeutronField.get_neutron_flux() as int
	$NeutronFlux/Readout.text = "Nuetron Flux: %d" % flux
	$NeutronFlux/Graph.write_data((flux * 2) + 1) # +1 so it's visible when zero
	
	var neutrons: int = $NeutronField.num_neutrons()
	var scaleTrip := 500
	var scale := 1
	if neutrons > scaleTrip:
		scale = (ceil(neutrons as float / scaleTrip as float) as float) * 1.5
	$NeutronPopulation/Readout.text = "Neutrons: %d [x%d]" % [neutrons, scale]
	$NeutronPopulation/Graph.scale = scale
	$NeutronPopulation/Graph.write_data(neutrons)


func _on_BiproductUpdateTimer_timeout():
	$BiproductMap.update()
