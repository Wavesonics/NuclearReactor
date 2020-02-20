extends Node2D
class_name Reactor

export(NodePath) var core_path: NodePath
onready var core_node := get_node(core_path) as Area2D

var collisionShape: CollisionShape2D

var heat_grid_draw_pos := Vector2(-200, 0)
const HEAT_GRID_RESOLUTION = 0.16
var heat_grid := []

var biproduct_grid_draw_pos := Vector2(-200, 200)
const BIPRODUCT_GRID_RESOLUTION = 0.16
var biproduct_grid := []

const decayTimeLimit := 1.0
var decayTimer := 0.0
var decayRate := 0.1

func _ready():
	self.collisionShape = core_node.get_node("CollisionShape2D") as CollisionShape2D
	var shape := self.collisionShape.shape as RectangleShape2D
	var width := shape.extents.x * 2.0
	var height := shape.extents.y * 2.0
	
	var yCells := floor(height * HEAT_GRID_RESOLUTION) as int
	var xCells := floor(width * HEAT_GRID_RESOLUTION) as int
	
	# Fill the grid with zeros
	heat_grid.resize(yCells)
	for iY in range(0, yCells, 1):
		heat_grid[iY] = []
		heat_grid[iY].resize(xCells)
		
		for iX in range(0, xCells, 1):
			heat_grid[iY][iX] = 0.0
	
	# Fill the grid with zeros
	biproduct_grid.resize(yCells)
	for iY in range(0, yCells, 1):
		biproduct_grid[iY] = []
		biproduct_grid[iY].resize(xCells)
		
		for iX in range(0, xCells, 1):
			biproduct_grid[iY][iX] = 0.0


func _physics_process(delta):
	
	decayTimer += delta
	if decayTimer >= decayTimeLimit:
		decayTimer = 0.0
		
		for iY in range(0, biproduct_grid.size(), 1):
			for iX in range(0, biproduct_grid[iY].size(), 1):
				var magnitude := biproduct_grid[iY][iX] as float
				# Decay biproducts
				biproduct_grid[iY][iX] = magnitude - decayRate
				#if magnitude / 10.0
		
		update()


func add_heat(global_pos: Vector2, magnitude: float = 1.0):
	var pos = to_local(global_pos)
	var gridY = floor(pos.y * HEAT_GRID_RESOLUTION) as int
	var gridX = floor(pos.x * HEAT_GRID_RESOLUTION) as int
	
	heat_grid[gridY][gridX] += magnitude

func add_fission_biproduct(global_pos: Vector2, magnitude: float = 1.0):
	var pos = to_local(global_pos)
	var gridY = floor(pos.y * BIPRODUCT_GRID_RESOLUTION) as int
	var gridX = floor(pos.x * BIPRODUCT_GRID_RESOLUTION) as int
	
	biproduct_grid[gridY][gridX] += magnitude

var rectSide := 2.0
var rectSize := Vector2(rectSide, rectSide)

func _draw():
	for iY in range(0, heat_grid.size(), 1):
		for iX in range(0, heat_grid[iY].size(), 1):
			var tempature := heat_grid[iY][iX] as float
			
			var rectPos := Vector2(iX * rectSide, iY * rectSide)
			var rect := Rect2(rectPos + heat_grid_draw_pos, rectSize)
			draw_rect(rect, Color(tempature / 10.0, 0.0, 0.0))
	
	for iY in range(0, biproduct_grid.size(), 1):
		for iX in range(0, biproduct_grid[iY].size(), 1):
			var magnitude := biproduct_grid[iY][iX] as float
			
			var rectPos := Vector2(iX * rectSide, iY * rectSide)
			var rect := Rect2(rectPos + biproduct_grid_draw_pos, rectSize)
			draw_rect(rect, Color(magnitude / 10.0, 0.0, 0.0))
