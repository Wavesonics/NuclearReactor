tool
extends Spatial

onready var controlRodPanelScene := preload("res://actors/3d_control_panel/ControlRodPanel.tscn")

func _ready():
	var initialXoffset := 0.0
	var width := 0.3
	
	if Engine.editor_hint:
		var ii := 0
		for rod in range(0, 2):
			var node := controlRodPanelScene.instance()
			$ControlRods.add_child(node)
			node.translation.x = initialXoffset - (width * ii)
			ii += 1
	else:
		var ii := 0
		for rod in ControlSystem.controlRods:
			var node := controlRodPanelScene.instance()
			node.set_control_rod(rod, ii)
			$ControlRods.add_child(node)
			node.translation.x = initialXoffset + (width * ii)
			ii += 1


func _on_ScramButton_button_pressed():
	ControlSystem.scram = true


func _on_FluxUpdateTimer_timeout():
	var flux := ControlSystem.neutronField.get_neutron_flux() as int
	$NeutronFluxLabel.set_label_text("Neutron Flux: %d" % flux)
	
	if flux > 0:
		for ii in range(0, flux):
			$GeigerCounter.play()
