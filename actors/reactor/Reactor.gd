extends Node2D
class_name Reactor

export(NodePath) var core_path: NodePath
onready var core_node := get_node(core_path) as Area2D

var collisionShape: CollisionShape2D

onready var neutronField := get_tree().get_nodes_in_group("neutron_field")[0] as NeutronField

var reactorWidth: float
var reactorHeight: float

var heat_grid_draw_pos := Vector2(-200, 0)
const HEAT_GRID_RESOLUTION := 64.0
var heat_grid := []
var heat_grid_cell_width: float
var heat_grid_cell_height: float

var biproduct_grid_draw_pos := Vector2(-200, 200)
const BIPRODUCT_GRID_RESOLUTION := 64.0
var biproduct_grid := []
var biproduct_cell_width: float
var biproduct_cell_height: float

const BIPRODUCT_FISION_RATE := 0.5
const biproductDecayRate := 0.0005


func _ready():
	self.collisionShape = core_node.get_node("CollisionShape2D") as CollisionShape2D
	var shape := self.collisionShape.shape as RectangleShape2D
	reactorWidth = shape.extents.x * 2.0
	reactorHeight = shape.extents.y * 2.0
	
	#################################
	# Heat
	#################################
	
	heat_grid_cell_height = floor(reactorHeight / HEAT_GRID_RESOLUTION) as int
	heat_grid_cell_width = floor(reactorWidth / HEAT_GRID_RESOLUTION) as int
	
	# Fill the grid with zeros
	heat_grid.resize(HEAT_GRID_RESOLUTION)
	for iY in range(0, HEAT_GRID_RESOLUTION, 1):
		heat_grid[iY] = []
		heat_grid[iY].resize(HEAT_GRID_RESOLUTION)
		
		for iX in range(0, HEAT_GRID_RESOLUTION, 1):
			heat_grid[iY][iX] = 0.0
	
	#################################
	# Biproducts
	#################################
	
	biproduct_cell_height = floor(reactorHeight / BIPRODUCT_GRID_RESOLUTION) as int
	biproduct_cell_width = floor(reactorWidth / BIPRODUCT_GRID_RESOLUTION) as int
	
	# Fill the grid with zeros
	biproduct_grid.resize(BIPRODUCT_GRID_RESOLUTION)
	for iY in range(0, BIPRODUCT_GRID_RESOLUTION, 1):
		biproduct_grid[iY] = []
		biproduct_grid[iY].resize(BIPRODUCT_GRID_RESOLUTION)
		
		for iX in range(0, BIPRODUCT_GRID_RESOLUTION, 1):
			biproduct_grid[iY][iX] = 0.0


func _physics_process(delta):
	process_biproducts()


func add_heat(global_pos: Vector2, magnitude: float = 1.0):
	var pos = to_local(global_pos)
	var gridY = floor(pos.y / heat_grid_cell_height) as int
	var gridX = floor(pos.x / heat_grid_cell_width) as int
	
	heat_grid[gridY][gridX] += magnitude

func add_fission_biproduct(global_pos: Vector2, magnitude: float = 0.1):
	var pos = to_local(global_pos)
	var gridY = floor(pos.y / biproduct_cell_height) as int
	var gridX = floor(pos.x / biproduct_cell_width) as int
	
	var oldMag := biproduct_grid[gridY][gridX] as float
	biproduct_grid[gridY][gridX] = min(oldMag+magnitude, 0.50 )


func process_biproducts():
	for iY in range(0, biproduct_grid.size(), 1):
		for iX in range(0, biproduct_grid[iY].size(), 1):
			var magnitude := biproduct_grid[iY][iX] as float
			
			# Decay
			biproduct_grid[iY][iX] = max(0.0, magnitude - biproductDecayRate)
			
			var chance := magnitude / 100.0
			var real := rand_range(0.001, 1.0)
			if chance > real:
				#print("BI %f vs %f" % [chance, real])
				var pos := Vector2(position.x + (biproduct_cell_width * iX), position.y + (biproduct_cell_height * iY))
				var vel := neutronField.random_direction() * neutronField.SPEED_THERMAL
				neutronField.spawn_neutron(pos, vel)


var rectSide := 2.0
var rectSize := Vector2(rectSide, rectSide)

func _draw():
	return
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
			draw_rect(rect, Color(magnitude, 0.0, 0.0))


func _on_MapUpdateTimer_timeout():
	update()
