extends Spatial

func _ready():
	vr.initialize()


func _on_FpsTimer_timeout():
	var fps := Engine.get_frames_per_second()
	$FpsLabel.set_label_text("%d fps" % fps)
