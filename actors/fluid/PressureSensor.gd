tool
extends Node2D

export(NodePath) onready var pipePath: NodePath setget set_pipe_path
onready var pipe = get_node(pipePath)

export(DynamicFont) var font: DynamicFont

export(bool) var enableRendering := true setget set_enable_rendering
export(bool) var autoUpdating := true
var timeSinceLastUpdate := 0.0
export(float) var updateThreshold := 1.0

var lastReadValue := 0.0

func set_pipe_path(value):
	pipePath = value
	pipe = get_node(pipePath)
	update()

func set_enable_rendering(value):
	enableRendering = value
	update()

func _ready():
	update()


func _process(delta):
	if Engine.editor_hint:
		return
	
	if autoUpdating:
		timeSinceLastUpdate += delta
		if timeSinceLastUpdate >= updateThreshold:
			timeSinceLastUpdate = 0.0
			read_preasure()
			update()


func read_preasure():
	lastReadValue = pipe.read_initial_pressure()


func _draw():
	if not enableRendering:
		return
	
	if pipe != null:
		var toPos = to_local(pipe.global_position)
		draw_line(Vector2(), toPos, Color.blue, 4.0)
	
	draw_circle(Vector2(), 20.0, Color.black)
	if font != null:
		draw_string(font, Vector2(), "%d" % lastReadValue)
