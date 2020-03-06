extends Node

func _ready():
	if OS.has_feature("vr"):
		get_tree().change_scene("res://vr/VrGame.tscn")
	else:
		get_tree().change_scene("res://GameCpp.tscn")
