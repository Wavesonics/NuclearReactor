tool
extends Node2D
class_name CoolantPipe


export(int) var numSegments := 10
var segmentWidth := 16.0
var segmentHeight := 32.0
var boundingBox: Rect2

var maxPressure := 100.0
var minPressure := 0.0

var initialPressure := maxPressure

export(NodePath) var previousPipePath: NodePath
var previousPipe = null

export(bool) var enableRendering := true

var outputPressure: float
var segments := []

onready var debugFont := load("res://vr/DefaultFont.tres") as DynamicFont


func _ready():
	update()
	
	boundingBox = Rect2(0.0, 0.0, segmentWidth, (segmentHeight * numSegments) + (numSegments*2.0))
	
	for ii in range(numSegments):
		segments.push_back(randf() * initialPressure)
	
	if Engine.editor_hint:
		return
	
	add_to_group("pipes")
	
	if previousPipePath != null:
		previousPipe = get_node(previousPipePath)


func _draw():
	if not enableRendering:
		return
	
	for ii in range(numSegments):
		var segmentPressure = segments[ii]
		var c = Util.value_to_heatmap(segmentPressure, minPressure, maxPressure)
		var y := (ii * segmentHeight) + (ii*2.0)
		draw_rect(Rect2(0.0, y, segmentWidth, segmentHeight), c)
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


func get_pressure(globalPos: Vector2) -> float:
	var segmentIndex := to_segment(globalPos)
	if segmentIndex > -1:
		return segments[segmentIndex]
	else:
		return -1.0


func set_pressure(segmentIndex: int, newValue: float):
	segments[segmentIndex] = newValue


func set_pressure_by_position(globalPos: Vector2, newValue: float):
	var segmentIndex := to_segment(globalPos)
	if segmentIndex > -1:
		segments[segmentIndex] = newValue
