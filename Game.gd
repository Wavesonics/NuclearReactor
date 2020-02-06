extends Control

export(NodePath) var reactor_path: NodePath
onready var reactor_node := get_node(reactor_path) as Reactor

export(NodePath) var neutron_field_path: NodePath
onready var neutron_field_node := get_node(neutron_field_path) as NeutronField

func _process(delta):
	var neutrons := neutron_field_node.num_neutrons()
	$NeutronPopulation/Readout.text = "Neutrons: %d" % neutrons
	$NeutronPopulation/Graph.write_data(neutrons)

func _on_NeutronButton_pressed():
	reactor_node.spawn_neutron()
