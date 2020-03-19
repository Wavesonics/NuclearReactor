extends Object
class_name Util


static func value_to_heatmap(value: float, minimum: float, maximum: float) -> Color:
	if value < minimum:
		return Color.black;
	else:
		var halfmax := (maximum - minimum) / 2.0
		var b = max(0.0, (1.0 - (value - minimum) / halfmax))
		var r = max(0.0, ((value - minimum) / halfmax - 1))
		var g = 1.0 - b - r
		return Color(r, g, b);


static func value_to_coldmap(value: float, minimum: float, maximum: float) -> Color:
	if value < minimum:
		return Color(0.0, 0.0, 0.0, 0.0);
	else:
		var halfmax := (maximum - minimum) / 2.0
		
		
		var b = max(0.0, ((value - minimum) - halfmax) / halfmax)
		var r = 0.0
		var g = 0.0
		var a := max(0.5, ((value - minimum) / maximum))
		return Color(r, g, b, a);
