tool
extends Node2D

export(NodePath) var previousPipePath: NodePath
onready var previousPipe = get_node(previousPipePath)

export(Array, NodePath) var nextPipePaths: Array
var nextPipes := []

export(bool) var enableRendering := true

var outputPressure := 0.0

func _ready():
	update()
	if Engine.editor_hint:
		return
	
	add_to_group("pipe_joints")
	
	if not nextPipePaths.empty():
		for pipePath in nextPipePaths:
			nextPipes.push_back(get_node(pipePath))


func fluid_tick():	
	outputPressure = previousPipe.consume_output(self)


func consume_output(consumer) -> float:
	return outputPressure / nextPipes.size()


func _draw():
	if not enableRendering:
		return
	
	draw_circle(Vector2(), 10.0, Color.green)
