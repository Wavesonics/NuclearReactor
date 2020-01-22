extends RigidBody2D
class_name Neutron

const SPEED_RELATIVISTIC := 100.0
const SPEED_THERMAL := 10.0

const DRAW_RADIUS := 5
var draw_color := Color.gray

const CROSS_SECTION_RELATIVISTIC := 0.99
const CROSS_SECTION_THERMAL := 0.50

func _ready():
	pass

func _draw():
	draw_circle(position, DRAW_RADIUS, draw_color)

func _physics_process(delta):
	var fuel_rods = get_tree().get_nodes_in_group("fuel_rods")
	for rod in fuel_rods:
		if rod.overlaps_body(self):
			var crossSection: float
			if self.linear_velocity.length() > (SPEED_THERMAL + 1.0):
				crossSection = CROSS_SECTION_RELATIVISTIC
			else:
				crossSection = CROSS_SECTION_THERMAL
			
			if rand_range(0.0, 1.0) >= crossSection:
				rod.fission(self)
			
			break