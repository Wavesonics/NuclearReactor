extends Area2D
class_name Moderator
tool

export(NodePath) var collision_shape_path: NodePath
onready var collision_shape_node := get_node(collision_shape_path) as CollisionShape2D

const MODERATOR_CROSS_SECTION := 0.10
var rect : Rect2

var neutron_field: NeutronField


func _ready():
	var size := collision_shape_node.shape.extents as Vector2
	self.rect = Rect2(Vector2(-size.x, -size.y), Vector2(size.x*2, size.y*2))
	self.neutron_field = get_tree().get_nodes_in_group("neutron_field")[0] as NeutronField


func _draw():
	draw_rect(self.rect, Color.blue)


func process_neutron(neutron: Array):
	var pos := neutron[0] as Vector2
	var vel := neutron[1] as Vector2
	var speed := vel.length()
	
	# Only interact with relativistic neutrons
	if speed > NeutronField.SPEED_THERMAL + 1.0:
		if rand_range(0.0, 1.0) >= (1.0 - MODERATOR_CROSS_SECTION):
			
			# Refect
			var thermalizedVel := vel * -1.0
			# Don't reflect perfectly back
			thermalizedVel.x += rand_range(-0.3, 0.3)
			thermalizedVel.y += rand_range(-0.3, 0.3)
			# Slow down
			thermalizedVel = thermalizedVel.normalized() * NeutronField.SPEED_THERMAL
			
			neutron_field.spawn_neutron(pos, thermalizedVel)
			return true
		else:
			return false
	else:
		return false
