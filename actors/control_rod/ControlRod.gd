extends Area2D
class_name ControlRod
tool

export(NodePath) var collision_shape_path: NodePath
onready var collision_shape_node := get_node(collision_shape_path) as CollisionShape2D

const CONTROL_CROSS_SECTION := 0.50
const SPEED := 1.0
const SPEED_SCRAM := 10.0

var rect : Rect2
var fullOutPositionDelta: float
var fullInPosition: float
var currentPositionDelta: float = 0.0

var scram := false

func scram():
	scram = true

func _ready():
	var size := collision_shape_node.shape.extents as Vector2
	self.rect = Rect2(Vector2(-size.x, -size.y), Vector2(size.x*2, size.y*2))
	
	self.fullOutPositionDelta = size.y*2
	self.fullInPosition = self.position.y


func _draw():
	draw_rect(self.rect, Color.green)


func percent_in():
	var totalDistance = abs(self.fullOutPositionDelta)
	var curPos = abs(self.currentPositionDelta)
	
	if curPos > 0.0:
		return curPos / totalDistance
	else:
		return 0.0


func process_neutron(neutron: Array):
	if rand_range(0.0, 1.0) >= CONTROL_CROSS_SECTION:
		return true
	else:
		return false


func _process(delta):
	if Engine.is_editor_hint():
		return
	
	var changed := false
	
	if scram:
		if percent_in() > 0.0:
			self.currentPositionDelta += SPEED_SCRAM
			changed = true
		else:
			scram = false
	else:
		if Input.is_action_pressed("ui_up"):
			self.currentPositionDelta -= SPEED
			changed = true
		elif Input.is_action_pressed("ui_down"):
			self.currentPositionDelta += SPEED
			changed = true
	
	if changed:
		self.currentPositionDelta = clamp(self.currentPositionDelta, -self.fullOutPositionDelta, 0.0)
		self.position.y = self.fullInPosition + self.currentPositionDelta
