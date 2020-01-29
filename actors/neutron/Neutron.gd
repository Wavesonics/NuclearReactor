extends RigidBody2D
class_name Neutron

const SPEED_RELATIVISTIC := 100.0
const SPEED_THERMAL := 10.0

const DRAW_RADIUS := 5
var draw_color := Color.gray

#const CROSS_SECTION_RELATIVISTIC := 0.99
const CROSS_SECTION_RELATIVISTIC := 0.975
const CROSS_SECTION_THERMAL := 0.50

const CONTROL_CROSS_SECTION := 0.50

var fuel_rods
var control_rods

func _ready():
	self.fuel_rods = get_tree().get_nodes_in_group("fuel_rods")
	self.control_rods = get_tree().get_nodes_in_group("control_rods")

func _draw():
	draw_circle(Vector2.ZERO, DRAW_RADIUS, draw_color)

func _physics_process(delta):
	
	for rod in self.fuel_rods:
		if rod.overlaps_body(self):
			var crossSection: float
			if self.linear_velocity.length() > (SPEED_THERMAL + 1.0):
				crossSection = CROSS_SECTION_RELATIVISTIC
			else:
				crossSection = CROSS_SECTION_THERMAL
			
			if rand_range(0.0, 1.0) >= crossSection:
				rod.fission(self)
			
			break
	
	for rod in self.control_rods:
		if rod.overlaps_body(self):
			if rand_range(0.0, 1.0) >= CONTROL_CROSS_SECTION:
				rod.capture(self)
			break
