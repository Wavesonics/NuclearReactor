extends "res://OQ_Toolkit/OQ_Interactables/scripts/OQ_ButtonPressable.gd"

signal button_released

func _ready():
	$ButtonArea.connect("area_exited", self, "_on_ButtonArea_area_exited_momentary")


func _on_ButtonArea_area_exited_momentary():
	button_released()


func button_released():
	is_on = false
	switch_mat(is_on)
	emit_signal("button_released")
