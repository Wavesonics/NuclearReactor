extends Node2D
class_name Reactor

onready var neutron_scene := preload("res://actors/neutron/Neutron.tscn")

export(NodePath) var core_path: NodePath
onready var core_node := get_node(core_path) as Area2D

func _ready():
	pass

#func spawn_neutron():
#	var neutron = neutron_scene.instance()
#
#	var margin := 0.1
#	var areaShape = core_node.get_node("CollisionShape2D") as CollisionShape2D
#	var area = areaShape.shape as RectangleShape2D
#
#	core_node.add_child(neutron)
#
#	# Random position inside of reactor core
#	neutron.position = Vector2(rand_range(margin, area.extents.x-margin), rand_range(margin, area.extents.y-margin))
#	print(neutron.position)
#
#	# Random direction at relativistic speed
#	var direction = Vector2(rand_range(0.1, 1.0), rand_range(0.1, 1.0)).normalized()
#	direction *= Neutron.SPEED_RELATIVISTIC
#	neutron.apply_central_impulse(direction)

func _on_Core_body_exited(body):
	
	#body.get_parent().remove_child(body)
	body.queue_free()
	#print("Neutron escaped core")
	pass