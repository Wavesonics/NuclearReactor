extends Area2D
class_name FuelRod
tool

export(NodePath) var collision_shape_path: NodePath
onready var collision_shape_node := get_node(collision_shape_path) as CollisionShape2D

onready var reactor := get_tree().get_nodes_in_group("reactors")[0] as Reactor
onready var neutron_field := get_tree().get_nodes_in_group("neutron_field")[0] as NeutronField

var rect : Rect2

const CROSS_SECTION_RELATIVISTIC := 0.001
const CROSS_SECTION_THERMAL := 0.05

var _time_sinc_last_fission := 0.0
const SPANTANEUOS_FISION_RATE := 0.5


func _ready():
	var size := collision_shape_node.shape.extents as Vector2
	self.rect = Rect2(Vector2(-size.x, -size.y), Vector2(size.x*2, size.y*2))


func _draw():
	draw_rect(self.rect, Color.red)


func _physics_process(delta):
	if Engine.is_editor_hint():
		return
	
	_time_sinc_last_fission += delta
	if _time_sinc_last_fission >= SPANTANEUOS_FISION_RATE:
		_time_sinc_last_fission = 0.0
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
	
	if rand_range(0.0, 1.0) >= (1.0 - crossSection):
		fission(pos)
		return true
	else:
		return false


func spawn_neutron(pos: Vector2):
	var direction = Vector2(rand_range(0.0, 1.0), rand_range(0.0, 1.0)).normalized()
	if randi() % 2 == 0:
		direction.x *= -1
	if randi() % 2 == 0:
		direction.y *= -1
	direction *= NeutronField.SPEED_RELATIVISTIC
	
	neutron_field.spawn_neutron(pos, direction)


func fission(fission_position: Vector2):
	spawn_neutron(fission_position)
	spawn_neutron(fission_position)
	
	reactor.add_heat(fission_position)
