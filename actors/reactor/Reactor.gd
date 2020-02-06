extends Node2D
class_name Reactor

export(NodePath) var core_path: NodePath
onready var core_node := get_node(core_path) as Area2D

var collisionShape: CollisionShape2D

func _ready():
	self.collisionShape = core_node.get_node("CollisionShape2D") as CollisionShape2D
