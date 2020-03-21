extends "res://entry/3d/BaseGame3d.gd"


func _ready():
	vr.initialize()


func _on_FpsUpdateTimer_timeout():
	var fps := Engine.get_frames_per_second()
	$FpsLabel.set_label_text("%d fps" % fps)
