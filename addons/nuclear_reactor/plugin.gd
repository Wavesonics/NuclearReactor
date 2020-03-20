tool
extends EditorPlugin


func _enter_tree():
	add_custom_type("ReactorCoreCpp", "Node2D", preload("res://actors/reactor/ReactorCoreCpp.gdns"), preload("res://addons/nuclear_reactor/node.png"))
	add_custom_type("ModeratorCpp", "Node2D", preload("res://actors/moderator/Moderator.gdns"), preload("res://addons/nuclear_reactor/node.png"))
	add_custom_type("ControlRodCpp", "Node2D", preload("res://actors/control_rod/ControlRodCpp.gdns"), preload("res://addons/nuclear_reactor/node.png"))
	add_custom_type("FuelRodCpp", "Node2D", preload("res://actors/fuel_rod/FuelRodcpp.gdns"), preload("res://addons/nuclear_reactor/node.png"))
	add_custom_type("Thermocouple", "Node2D", preload("res://actors/Thermocouple.gdns"), preload("res://addons/nuclear_reactor/node.png"))
	
	add_custom_type("CoolantPipe", "Node2D", preload("res://actors/fluid/CoolantPipe.gd"), preload("res://addons/nuclear_reactor/node.png"))
	add_custom_type("PipeSplit", "Node2D", preload("res://actors/fluid/PipeSplit.gd"), preload("res://addons/nuclear_reactor/node.png"))
	add_custom_type("PipeCombiner", "Node2D", preload("res://actors/fluid/PipeCombiner.gd"), preload("res://addons/nuclear_reactor/node.png"))
	add_custom_type("HeatSink", "Node2D", preload("res://actors/fluid/HeatSink.gd"), preload("res://addons/nuclear_reactor/node.png"))
	add_custom_type("PressureSensor", "Node2D", preload("res://actors/fluid/PressureSensor.gd"), preload("res://addons/nuclear_reactor/node.png"))
	
	add_custom_type("Heatmap", "Node2D", preload("res://actors/HeatMap.gdns"), preload("res://addons/nuclear_reactor/node.png"))
	add_custom_type("DiffusingHeatMap", "Node2D", preload("res://actors/DiffusingHeatMap.gdns"), preload("res://addons/nuclear_reactor/node.png"))
	
	add_custom_type("NeutronField", "Node2D", preload("res://actors/neutron_field/NeutronFieldCpp.gdns"), preload("res://addons/nuclear_reactor/node.png"))


func _exit_tree():
	remove_custom_type("ReactorCoreCpp")
	remove_custom_type("ModeratorCpp")
	remove_custom_type("ControlRodCpp")
	remove_custom_type("FuelRodCpp")
	remove_custom_type("Thermocouple")
	
	remove_custom_type("CoolantPipe")
	remove_custom_type("PipeSplit")
	remove_custom_type("PipeCombiner")
	remove_custom_type("HeatSink")
	remove_custom_type("PressureSensor")
	
	remove_custom_type("Heatmap")
	remove_custom_type("DiffusingHeatMap")
	
	remove_custom_type("NeutronField")
