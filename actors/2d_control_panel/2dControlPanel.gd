extends Control

onready var controlRodPanelScene := preload("res://actors/2d_control_panel/ControlRodPanel.tscn")

func _ready():
	for rod in ControlSystem.controlRods:
		var node := controlRodPanelScene.instance()
		node.controlRod = rod
		add_child(node)


func _on_ScramButton_pressed():
	ControlSystem.scram = true
