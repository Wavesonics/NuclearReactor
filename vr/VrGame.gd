extends Spatial

func _ready():
	vr.initialize()


func _on_TestButton_button_pressed():
	print("VR Button pressed")
