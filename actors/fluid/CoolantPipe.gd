tool
extends Node2D
class_name CoolantPipe


export(int) var numSegments := 10 setget set_num_segments
var segmentWidth := 16.0
var segmentHeight := 32.0
var boundingBox: Rect2

var maxPressure := 1000.0
var minPressure := 0.0

var initialPressure := maxPressure / 10.0

export(NodePath) var thermalMapPath: NodePath
var thermalMap = null

export(NodePath) var previousPipePath: NodePath setget set_prev_pipe
var previousPipe = null

var neutronField = null

export(bool) var enableRendering := true
export(bool) var enableDebugRendering := false

var endPoint: Vector2

var outputPressure: float
var segments := []

onready var debugFont := load("res://vr/DefaultFont.tres") as DynamicFont


func set_num_segments(n: int):
	numSegments = n
	
	if Engine.editor_hint:
		initialize()


func set_prev_pipe(prevPath: NodePath):
	previousPipePath = prevPath
	
	if Engine.editor_hint:
		initialize()


func get_global_end_point() -> Vector2:
	return to_global(endPoint)

func initialize():
	boundingBox = Rect2(0.0, 0.0, segmentWidth, (segmentHeight * numSegments) + (numSegments*2.0))
	
	endPoint = Vector2(boundingBox.size.x/2.0, boundingBox.size.y)
	
	if thermalMapPath != null:
		thermalMap = get_node(thermalMapPath)
	
	segments.clear()
	for ii in range(numSegments):
		segments.push_back(randf() * initialPressure)
	
	previousPipe = null
	if previousPipePath != null:
		previousPipe = get_node(previousPipePath)
	
	update()


func _ready():
	update()
	
	initialize()
	
	if Engine.editor_hint:
		return
	
	add_to_group("pipes")
	
	neutronField = ControlSystem.get_neutron_field()


func _physics_process(delta):
	if Engine.editor_hint:
		return
	
	var heatTransferAmmount := 2.0
	
	if thermalMap != null:
		for ii in range(numSegments):
			var x = segmentWidth / 2.0
			var y = (ii * segmentHeight) + (ii*2.0)
			var neutronSpace := position + Vector2(x, y).rotated(rotation)
			#var neutronSpace := pos.rotated(rotation)
			
			var gridPos := thermalMap.to_grid(neutronSpace) as Vector2
			
			var gridX := gridPos.x as int
			var gridY := gridPos.y as int
			
			if thermalMap.range_check(gridX, gridY):
				absorbe_heat(ii, gridX, gridY, heatTransferAmmount)
				# Also absorbe heat from the immedately neighbor
				absorbe_heat(ii, gridX-1, gridY, heatTransferAmmount)
				absorbe_heat(ii, gridX+1, gridY, heatTransferAmmount)


func absorbe_heat(index: int, gridX: int, gridY: int, heatTransferAmmount: float):
	#if thermalMap.range_check(gridX, gridY):
	var heat := thermalMap.read_magnitude(gridX, gridY) as float
	if heat > 0.0:
		thermalMap.add_heat(-heatTransferAmmount, gridX, gridY)
		add_pressure(index, heatTransferAmmount)


func _draw():
	if not enableRendering:
		return
	
	for ii in range(numSegments):
		var segmentPressure = segments[ii]
		var c = Util.value_to_heatmap(segmentPressure, minPressure, maxPressure)
		var y := (ii * segmentHeight) + (ii*2.0)
		draw_rect(Rect2(0.0, y, segmentWidth, segmentHeight), c)
		
		if previousPipe != null:
			if previousPipe.has_method("get_global_end_point"):
				var toPos = to_local(previousPipe.get_global_end_point())
				draw_line(Vector2(segmentWidth/2.0, 0.0), toPos, Color.blue, 4.0)
			else:
				var toPos = to_local(previousPipe.global_position)
				draw_line(Vector2(segmentWidth/2.0, 0.0), toPos, Color.blue, 4.0)
		
		if enableDebugRendering:
			draw_string(debugFont, Vector2(-20.0, y + (segmentHeight/2.0)), "[%d]" % ii)
			draw_string(debugFont, Vector2(segmentWidth + 5.0, y + (segmentHeight/2.0)), "%d" % segmentPressure)
			
			#draw_rect(boundingBox, Color.red)


func fluid_tick():
	# Store the last segment for transfer to the next pipe
	outputPressure = segments[numSegments-1]
	
	# Start at the end and move each segment forward once
	for ii in range(numSegments-1, 0, -1):
		segments[ii] = segments[ii-1]
	
	# Just fill the input with emptyness, this should be filled in
	# during the next step
	segments[0] = 0.0


func update_from_prev():
	if previousPipe != null:
		segments[0] = previousPipe.consume_output(self)
	else:
		segments[0] = 0.0


func consume_output(consumer) -> float:
	return outputPressure


func contains_point(globalPos: Vector2) -> bool:
	var pos = to_local(globalPos)
	return boundingBox.has_point(pos)


func to_segment(globalPos: Vector2) -> int:
	var pos = to_local(globalPos)
	if pos.x >= 0.0 and pos.x <= segmentWidth:
		var ii = floor(pos.y / (segmentHeight+2.0))
		if ii >= 0 and ii < numSegments:
			return ii
		else:
			return -1
	else:
		return -1


func read_initial_pressure() -> float:
	return segments[0]


func get_pressure(globalPos: Vector2) -> float:
	var segmentIndex := to_segment(globalPos)
	if segmentIndex > -1:
		return segments[segmentIndex]
	else:
		return -1.0


func add_pressure(segmentIndex: int, newValue: float):
	segments[segmentIndex] += newValue


func set_pressure(segmentIndex: int, newValue: float):
	segments[segmentIndex] = newValue


func set_pressure_by_position(globalPos: Vector2, newValue: float):
	var segmentIndex := to_segment(globalPos)
	if segmentIndex > -1:
		segments[segmentIndex] = newValue
