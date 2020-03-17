tool
extends Node2D
class_name CoolanPipe

var numSegments := 10
var segmentWidth := 16.0
var segmentHeight := 32.0

var initialPressure := 10.0

export(NodePath) var previousPipePath: NodePath
var previousPipe = null

export(NodePath) var nextPipePath: NodePath
var nextPipe = null

var outputSegment: float
var segments := []

onready var debugFont := load("res://vr/DefaultFont.tres") as DynamicFont


func _ready():
	add_to_group("pipes")
	
	if nextPipePath != null:
		nextPipe = get_node(nextPipePath)
	
	if previousPipePath != null:
		previousPipe = get_node(previousPipePath)
	
	for ii in range(numSegments):
		segments.push_back(randf() * initialPressure)
	
	update()

func _draw():
	var c = Color.blue
	for ii in range(numSegments):
		var segmentPressure = segments[ii]
		c.a = (segmentPressure / initialPressure)
		var y := (ii * segmentHeight) + (ii*2.0)
		draw_rect(Rect2(0.0, y, segmentWidth, segmentHeight), c)
		draw_string(debugFont, Vector2(-20.0, y + (segmentHeight/2.0)), "[%d]" % ii)
		draw_string(debugFont, Vector2(segmentWidth + 5.0, y + (segmentHeight/2.0)), "%d" % segmentPressure)


func fluid_tick():
	# Store the last segment for transfer to the next pipe
	outputSegment = segments[numSegments-1]
	
	# Start at the end and move each segment forward once
	for ii in range(numSegments-1, 0, -1):
		segments[ii] = segments[ii-1]
	
	# Just fill the input with emptyness, this should be filled in
	# during the next step
	segments[0] = 0.0
	#update()


func update_from_prev():
	if previousPipe != null:
		segments[0] = previousPipe.consume_output()
	else:
		segments[0] = 0.0


func consume_output() -> float:
	return outputSegment
