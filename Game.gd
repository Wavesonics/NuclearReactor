extends Control

export(NodePath) var reactor_path: NodePath
onready var reactor_node := get_node(reactor_path) as Reactor

func _process(delta):
	var num_neutrons = get_tree().get_nodes_in_group("neutrons").size()
	$NeutronCount.text = str(num_neutrons)

func _on_NeutronButton_pressed():
	reactor_node.spawn_neutron()
