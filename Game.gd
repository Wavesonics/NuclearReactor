extends Control

export(NodePath) var reactor_path: NodePath
onready var reactor_node := get_node(reactor_path) as Reactor

onready var neutron_field_node := get_tree().get_nodes_in_group("neutron_field")[0] as NeutronField


func _process(delta):
	$FpsLabel.text = "%d fps" % Engine.get_frames_per_second()
	
	if neutron_field_node != null:
		var neutrons := neutron_field_node.num_neutrons()
		$NeutronPopulation/Readout.text = "Neutrons: %d" % neutrons
		$NeutronPopulation/Graph.write_data(neutrons)
	
	if Input.is_action_just_released("scram"):
		var controlRods := get_tree().get_nodes_in_group("control_rods")
		for rod in controlRods:
			rod.scram()


# Debug neutron spawn
func _on_NeutronButton_pressed():
	reactor_node.spawn_neutron()
