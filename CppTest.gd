extends Control

func _ready():
	#$NeutronField.reactorCore = AABB2d.new()
	#for ii in range(0,10):
		#$NeutronField.createNeutron(Vector2(50.0, 50.0), Vector2(10.0, 10.0))
	print("adding")
	$NeutronField.createNeutron(Vector2(50.0, 50.0), Vector2(10.0, 10.0))
	print("added")

func _process(delta):
	var n: int = $NeutronField.numNeutrons()
	#print("Neutrons: %d" % n)
