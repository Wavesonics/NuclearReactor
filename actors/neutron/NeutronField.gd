extends Node2D
class_name NeutronField

onready var reactor := get_tree().get_nodes_in_group("reactors")[0] as Reactor
var reactor_core: Area2D

const GROUP := "neutron_field"

const SPEED_RELATIVISTIC := 100.0
const SPEED_THERMAL := 50.0

const DRAW_RADIUS := 1
var draw_color_thermal := Color.gray
var draw_color_relativistic := Color.orange

var reactorShape: Shape2D
var space_state: Physics2DDirectSpaceState

var enable_draw := true

var neutrons := []

var stillWorking := 0
var toRemove := []
var curDelta := 0.0

var neutronWaitSemaphore := Semaphore.new()
var neutronRemovalMutex := Mutex.new()

func _ready():
	self.reactor_core = self.reactor.core_node
	self.reactorShape = self.reactor.collisionShape.shape as Shape2D
	
	self.space_state = get_world_2d().get_direct_space_state()
	
	if OS.has_feature("vr"):
		enable_draw = false


func num_neutrons() -> int:
	return neutrons.size()


func spawn_neutron(pos: Vector2, vel: Vector2):
	var neutron := []
	#neutron.resize(2)
	neutron.append(pos)
	neutron.append(vel)
	
	neutrons.append(neutron)
	
	update()


func process_neutrons(batch: Array):
	#print("Neutron thread %d WOKE UP!! %d neutrons" % [batch[0], batch.size()])
	
	var iN = 0
	
	for index in batch:
		var neutron = neutrons[index]
		var pos := neutron[0] as Vector2
		var vel := neutron[1] as Vector2
		
		# Update the neutron's position from it's velocity
		var distanceMoved = vel * curDelta
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
			remove_neutron(iN)
		
		iN += 1

	# Let everyone know we're done
	self.stillWorking -= 1
	self.neutronWaitSemaphore.post()


func _physics_process(delta):
	
	self.toRemove.clear()
	self.curDelta = delta
	
	var numNuetrons := num_neutrons()
	var numWorkers := OS.get_processor_count()
	
	if numNuetrons > 0:
		var batchSize := 0
		# Just use one worker
		if numNuetrons < numWorkers:
			batchSize = numNuetrons
		else:
			batchSize = numNuetrons / numWorkers
		
		if batchSize <= numNuetrons:
			self.stillWorking = 1
			$ThreadPool.submit_task(self, "process_neutrons", range(0, num_neutrons()-1))
		else:
			self.stillWorking = numWorkers
			for ii in range(0, numWorkers-1):
				var batchStart := batchSize*ii
				var batch := range(batchStart, batchStart+batchSize)
				#print("Starting worker")
				$ThreadPool.submit_task(self, "process_neutrons", batch)
		
		#print("============================")
		
		while self.stillWorking > 0:
			#print("Still waiting... %d" % self.stillWorking)
			self.neutronWaitSemaphore.wait()
		
		self.toRemove.sort()
		
		# Remove in reverse order
		for iR in range(toRemove.size()-1, -1, -1):
			var ii = toRemove[iR]
			neutrons.remove(ii)
		
		update()

func remove_neutron(index: int):
	self.neutronRemovalMutex.lock()
	self.toRemove.append(index)
	self.neutronRemovalMutex.unlock()

func _draw():
	if enable_draw:
		var max_draw := 400
		var step := max(1, (neutrons.size() / max_draw))
		
		for neutronI in range(0, neutrons.size(), step):
			var neutron := neutrons[neutronI] as Array
			var pos = neutron[0] as Vector2
			var vel = neutron[1] as Vector2
			
			if vel.length() > (SPEED_THERMAL+1.0):
				draw_circle(pos, DRAW_RADIUS, draw_color_relativistic)
			else:
				draw_circle(pos, DRAW_RADIUS, draw_color_thermal)
