extends Area2D
class_name FuelRod

onready var neutron_scene := preload("res://actors/neutron/Neutron.tscn")

export(NodePath) var collision_shape_path: NodePath
onready var collision_shape_node := get_node(collision_shape_path) as CollisionShape2D

var rect : Rect2
var reactor

func _ready():
	var size := collision_shape_node.shape.extents as Vector2
	self.rect = Rect2(Vector2(-size.x, -size.y), Vector2(size.x*2, size.y*2))

	var reactors = get_tree().get_nodes_in_group("reactors")
	self.reactor = reactors[0]

func _draw():
	draw_rect(self.rect, Color.red)


func _physics_process(delta):
	if randf() > 0.95:
		spawn_random_neutron()


func spawn_random_neutron():
	var area = collision_shape_node.shape as RectangleShape2D

	# Random position inside of reactor core
	var half_w = area.extents.x / 2.0
	var half_h = area.extents.y / 2.0
	
	var pos = Vector2(rand_range(-half_w, half_w), rand_range(-half_h, half_h))
	spawn_neutron(pos)


func spawn_neutron(pos: Vector2):
	var neutron = neutron_scene.instance()
	add_child(neutron)
	neutron.position = pos
	
	# Random direction at relativistic speed
	var direction = Vector2(rand_range(1.0, 2.0), rand_range(1.0, 2.0)).normalized()
	if randi() % 2 == 0:
		direction.x *= -1
	if randi() % 2 == 0:
		direction.y *= -1
	direction *= Neutron.SPEED_RELATIVISTIC
	neutron.apply_central_impulse(direction)


func fission(neutron):
	#print("fission!")
	
	var fission_position = neutron.position
	#print("x %d y %d" % [fission_position.x, fission_position.y])

	neutron.queue_free()
	
	call_deferred("spawn_neutron", fission_position)
	call_deferred("spawn_neutron", fission_position)
	#spawn_neutron(fission_position)
	#spawn_neutron(fission_position)
