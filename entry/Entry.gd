extends Node

func _ready():
	if OS.has_feature("mobile_vr"):
		get_tree().change_scene("res://entry/3d/vr/mobile/Game3dVrMobile.tscn")
	else:
		vr.queue_free()
		get_tree().change_scene("res://entry/2d/Game2d.tscn")
