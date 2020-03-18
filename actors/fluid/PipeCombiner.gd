tool
extends Node2D

export(NodePath) var nextPipePath: NodePath
onready var nextPipe = get_node(nextPipePath)

export(Array, NodePath) var prevPipePaths: Array
var prevPipes := []

export(bool) var enableRendering := true

var outputPressure := 0.0

func _ready():
	update()
	if Engine.editor_hint:
		return
	
	add_to_group("pipe_joints")
	
	if not prevPipePaths.empty():
		for pipePath in prevPipePaths:
			prevPipes.push_back(get_node(pipePath))


func fluid_tick():	
	outputPressure = 0.0
	
	for pipe in prevPipes:
		outputPressure += pipe.consume_output(self)


func consume_output(consumer) -> float:
	return outputPressure


func _draw():
	if not enableRendering:
		return
	
	draw_circle(Vector2(), 10.0, Color.yellow)
