extends Control
class_name RealTimeGraph

var data := []
var size := 100
var nextWrite := 0

func _ready():
	self.data.resize(100)
	for ii in range(0, size-1):
		self.data[ii] = 0

func write_data(dataPoint: int):
	self.data[self.nextWrite] = dataPoint
	
	self.nextWrite += 1
	self.nextWrite %= size
	
	update()

func _draw():
	for ii in range(0, size-1):
		var n = self.data[ii]
		if ii == nextWrite:
			draw_line(Vector2(ii, 0), Vector2(ii, n), Color.orange)
		else:
			draw_line(Vector2(ii, 0), Vector2(ii, n), Color.red)
