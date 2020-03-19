extends Node

func _ready():
	if OS.has_feature("vr"):
		get_tree().change_scene("res://vr/VrGame.tscn")
	else:
		vr.queue_free()
		get_tree().change_scene("res://entry/2d/GameCpp.tscn")
