extends Control


func random_direction() -> Vector2:
	var direction = Vector2(rand_range(0.0, 1.0), rand_range(0.0, 1.0)).normalized()
	if randi() % 2 ==1:
		direction.x *= -1
	if randi() % 2 == 1:
		direction.y *= -1
	return direction


func _ready():
	for ii in range(0,1000):
		var velocity = random_direction() * 10.0
		var position = Vector2(rand_range(50.0, 450.0), rand_range(50.0, 450.0))
		$NeutronField.createNeutron(position, velocity)


func _process(delta):
	$FpsLabel.text = "%d fps" % Engine.get_frames_per_second()
	
	var neutrons: int = $NeutronField.numNeutrons()
	$NeutronPopulation/Readout.text = "Neutrons: %d" % neutrons
	$NeutronPopulation/Graph.write_data(neutrons)