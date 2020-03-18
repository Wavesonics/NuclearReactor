tool
extends Node2D

export(NodePath) var previousPipePath: NodePath setget set_prev_pipe
var previousPipe

export(Array, NodePath) var nextPipePaths: Array setget set_next_pipes
var nextPipes := []

export(bool) var enableRendering := true

var outputPressure := 0.0


func set_prev_pipe(value):
	previousPipePath = value
	initialize()


func set_next_pipes(value):
	nextPipePaths = value
	initialize()


func _ready():
	initialize()
	
	if Engine.editor_hint:
		return
	
	add_to_group("pipe_joints")


func initialize():
	previousPipe = null
	if previousPipePath != null:
		previousPipe = get_node(previousPipePath)
	
	nextPipes.clear()
	if nextPipePaths != null and not nextPipePaths.empty():
		for pipePath in nextPipePaths:
			if pipePath != null:
				nextPipes.push_back(get_node(pipePath))
	
	update()


func fluid_tick():
	if previousPipe != null:
		outputPressure = previousPipe.consume_output(self)


func consume_output(consumer) -> float:
	return outputPressure / nextPipes.size()


func _draw():
	if not enableRendering:
		return
	
	draw_circle(Vector2(), 10.0, Color.green)
	
	if previousPipe != null:
		if previousPipe.has_method("get_global_end_point"):
			var toPos = to_local(previousPipe.get_global_end_point())
			draw_line(Vector2(), toPos, Color.blue, 4.0)
	
	if not nextPipes.empty():
		for pipe in nextPipes:
			if pipe != null:
				if not pipe.has_method("get_global_end_point"):
					var toPos = to_local(pipe.global_position)
					draw_line(Vector2(0.0, 0.0), toPos, Color.blue, 4.0)
