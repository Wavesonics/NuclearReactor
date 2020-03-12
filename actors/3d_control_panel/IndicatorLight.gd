extends Spatial

var is_on := false


func _ready():
	set_on(false)


func set_on(on: bool):
	is_on = on
	if is_on:
		on()
	else:
		off()


func on():
	$On.show()
	$Off.hide()


func off():
	$On.hide()
	$Off.show()
