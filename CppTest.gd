extends Control


func _ready():
	#$NeutronField.reactorCore = AABB2d.new()
	#for ii in range(0,10):
		#$NeutronField.createNeutron(Vector2(50.0, 50.0), Vector2(10.0, 10.0))
	$NeutronField.createNeutron(Vector2(200.0, 200.0), Vector2(1.0, 1.0))


func _process(delta):
	var n: int = $NeutronField.numNeutrons()
	print("Neutrons: %d" % n)
