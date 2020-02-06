extends Area2D
class_name FuelRod
tool

export(NodePath) var collision_shape_path: NodePath
onready var collision_shape_node := get_node(collision_shape_path) as CollisionShape2D

var neutron_field: NeutronField

var rect : Rect2

#const CROSS_SECTION_RELATIVISTIC := 0.99
const CROSS_SECTION_RELATIVISTIC := 0.975
const CROSS_SECTION_THERMAL := 0.50

func _ready():
	var size := collision_shape_node.shape.extents as Vector2
	self.rect = Rect2(Vector2(-size.x, -size.y), Vector2(size.x*2, size.y*2))
	
	self.neutron_field = get_tree().get_nodes_in_group("neutron_field")[0] as NeutronField


func _draw():
	draw_rect(self.rect, Color.red)


func _physics_process(delta):
	if Engine.is_editor_hint():
		return
	
	if randf() > 0.95:
		spawn_random_neutron()


func spawn_random_neutron():
	var area = collision_shape_node.shape as RectangleShape2D

	# Random position inside of reactor core
	var half_w = area.extents.x
	var half_h = area.extents.y
	
	var rand_pos = Vector2(rand_range(-half_w, half_w), rand_range(-half_h, half_h))
	var spawn_pos = self.global_position + rand_pos 
	
	spawn_neutron(spawn_pos)


func process_neutron(neutron: Array):
	var pos := neutron[0] as Vector2
	var vel := neutron[1] as Vector2
	
	var crossSection: float
	if vel.length() > (NeutronField.SPEED_THERMAL + 1.0):
		crossSection = CROSS_SECTION_RELATIVISTIC
	else:
		crossSection = CROSS_SECTION_THERMAL
	
	if rand_range(0.0, 1.0) >= crossSection:
		fission(pos)
		return true
	else:
		return false


func spawn_neutron(pos: Vector2):
	var direction = Vector2(rand_range(1.0, 2.0), rand_range(1.0, 2.0)).normalized()
	if randi() % 2 == 0:
		direction.x *= -1
	if randi() % 2 == 0:
		direction.y *= -1
	direction *= NeutronField.SPEED_RELATIVISTIC
	
	neutron_field.spawn_neutron(pos, direction)


func fission(fission_position: Vector2):
	#print("fission!")

	spawn_neutron(fission_position)
	spawn_neutron(fission_position)
