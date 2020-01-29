extends Area2D
class_name ControlRod

export(NodePath) var collision_shape_path: NodePath
onready var collision_shape_node := get_node(collision_shape_path) as CollisionShape2D

var rect : Rect2

func _ready():
	var size := collision_shape_node.shape.extents as Vector2
	self.rect = Rect2(Vector2(-size.x, -size.y), Vector2(size.x*2, size.y*2))

func _draw():
	draw_rect(self.rect, Color.green)

func capture(neutron):
	neutron.queue_free()

func _process(delta):
	if Input.is_action_pressed("ui_up"):
		self.position.y -= 1
	elif Input.is_action_pressed("ui_down"):
		self.position.y += 1
