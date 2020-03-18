tool
extends Node2D

export(Array, NodePath) var prevPipePaths: Array setget set_prev_pipe_paths
var prevPipes := []

export(bool) var enableRendering := true

var outputPressure := 0.0


func set_prev_pipe_paths(value):
	prevPipePaths = value
	
	initialize()


func initialize():
	
	prevPipes.clear()
	if prevPipePaths != null and not prevPipePaths.empty():
		for pipePath in prevPipePaths:
			prevPipes.push_back(get_node(pipePath))
	
	update()


func _ready():
	initialize()
	
	if Engine.editor_hint:
		return
	
	add_to_group("pipe_joints")


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
	
	if not prevPipes.empty():
		for pipe in prevPipes:
			if pipe != null:
				if pipe.has_method("get_global_end_point"):
					var toPos = to_local(pipe.get_global_end_point())
					draw_line(Vector2(), toPos, Color.blue, 4.0)
				else:
					var toPos = to_local(pipe.global_position)
					draw_line(Vector2(), toPos, Color.blue, 4.0)
