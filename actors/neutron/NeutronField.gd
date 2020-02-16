extends Node2D
class_name NeutronField

onready var reactor := get_tree().get_nodes_in_group("reactors")[0] as Reactor
var reactor_core: Area2D

const GROUP := "neutron_field"

const SPEED_RELATIVISTIC := 100.0
const SPEED_THERMAL := 10.0

const DRAW_RADIUS := 5
var draw_color := Color.gray

var reactorShape: Shape2D
var space_state: Physics2DDirectSpaceState

var enable_draw := true

var neutrons := []

func _ready():
	self.reactor_core = self.reactor.core_node
	self.reactorShape = self.reactor.collisionShape.shape as Shape2D
	
	self.space_state = get_world_2d().get_direct_space_state()


func num_neutrons() -> int:
	return neutrons.size()


func spawn_neutron(pos: Vector2, vel: Vector2):
	var neutron := []
	#neutron.resize(2)
	neutron.append(pos)
	neutron.append(vel)
	
	neutrons.append(neutron)
	update()


func _physics_process(delta):
	
	var toRemove := []
	
	var iN = 0
	for neutron in neutrons:
		var pos := neutron[0] as Vector2
		var vel := neutron[1] as Vector2
		
		# Update the neutron's position from it's velocity
		var distanceMoved = vel * delta
		neutron[0] = pos + distanceMoved
		
		# Find all areas this Neutron collides with
		var collisions := self.space_state.intersect_point(neutron[0], 32, [], 2147483647, true, true) as Array
		
		var is_in_reactor_core := false
		var remove_neutron := false
		# Handle collision cases
		for collision in collisions:
			var collider := collision["collider"] as Node
			if collider == self.reactor_core:
				is_in_reactor_core = true
			elif collider.has_method("process_neutron"):
				if collider.process_neutron(neutron):
					remove_neutron = true
		
		if not is_in_reactor_core or remove_neutron:
			#print("Neutron escaped!")
			toRemove.append(iN)
		
		iN += 1
	
	# Remove in reverse order
	for iR in range(toRemove.size()-1, -1, -1):
		var ii = toRemove[iR]
		neutrons.remove(ii)
	
	update()

func _draw():
	if enable_draw:
		for neutron in neutrons:
			var pos = neutron[0]
			draw_circle(pos, DRAW_RADIUS, draw_color)
