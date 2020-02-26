extends Button
class_name MomentaryButton

var is_pressed := false


func _ready():
	connect("button_down", self, "button_down")
	connect("button_up", self, "button_up")


func button_down():
	is_pressed = true


func button_up():
	is_pressed = false
