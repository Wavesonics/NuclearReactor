extends Control

export(NodePath) var reactor_path: NodePath
onready var reactor_node := get_node(reactor_path) as Reactor

export(NodePath) var neutron_field_path: NodePath
onready var neutron_field_node := get_node(neutron_field_path) as NeutronField

func _ready():
	set_process_input(true)

func _process(delta):
	var neutrons := neutron_field_node.num_neutrons()
	$NeutronPopulation/Readout.text = "Neutrons: %d" % neutrons
	$NeutronPopulation/Graph.write_data(neutrons)

# Debug neutron spawn
func _on_NeutronButton_pressed():
	reactor_node.spawn_neutron()

func _input(ev):
	if ev is InputEventKey and ev.scancode == KEY_SPACE:
		var controlRods := get_tree().get_nodes_in_group("control_rods")
		for rod in controlRods:
			rod.scram()
