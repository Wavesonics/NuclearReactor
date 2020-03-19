tool
extends Node2D

export(NodePath) var previousPipePath: NodePath
onready var previousPipe = get_node(previousPipePath)

export(bool) var enableRendering := true

var pressure := 0.0
var outputPressure := 0.0
const coolingFactor := 2.0

func _ready():
	update()
	if Engine.editor_hint:
		return
	
	add_to_group("pipes")


func fluid_tick():
	pressure = pressure / coolingFactor


func update_from_prev():
	outputPressure = pressure
	pressure = previousPipe.consume_output(self)


func consume_output(consumer) -> float:
	return outputPressure


func _draw():
	if not enableRendering:
		return
	
	var size := 60.0
	var inset := 10.0
	
	var c = Util.value_to_heatmap(pressure, 0.0, 100.0)
	var c2 = Util.value_to_heatmap(pressure/coolingFactor, 0.0, 100.0)
	
	draw_rect(Rect2(Vector2(-size/2.0, -size/2.0), Vector2(size, size)),  Color.whitesmoke)
	
	draw_rect(Rect2(Vector2(-size/2.0 + (inset / 2.0), -size/2.0 + (inset / 2.0)), Vector2((size-10.0)/2.0, size-10.0)), c2)
	draw_rect(Rect2(Vector2(0.0, -size/2.0 + (inset / 2.0)), Vector2((size-10.0)/2.0, size-10.0)), c)
