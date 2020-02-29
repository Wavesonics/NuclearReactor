//
// Created by Adam on 2/27/2020.
//

#include "Area2d.h"
#include "../util/Utils.h"

using namespace nuclearPhysics;
using namespace godot;

Area2d::Area2d() : bottomLeft(Vector2()), topRight(Vector2())
{

}

Area2d::Area2d(const godot::Vector2 &bottomLeft, const godot::Vector2 &topRight)
		: bottomLeft(bottomLeft), topRight(topRight)
{
}

bool Area2d::contains(const godot::Vector2 &point) const
{
	return point.x > bottomLeft.x && point.x < topRight.x && point.y > bottomLeft.y && point.y < topRight.y;
}

float Area2d::width() const
{
	return topRight.x - bottomLeft.x;
}

float Area2d::height() const
{
	return topRight.y - bottomLeft.y;
}

std::ostream &operator<<(std::ostream &os, const Area2d &a)
{
	os << "Bottom Left" << a.bottomLeft << " Top Right: " << a.topRight << ")";
	return os;
}

std::ostream &operator<<(std::ostream &os, Area2d &a)
{
	os << "Bottom Left" << a.bottomLeft << " Top Right: " << a.topRight << ")";
	return os;
}

void Area2d::_register_methods()
{
	register_method("contains", &Area2d::contains);
	register_method("width", &Area2d::width);
	register_method("height", &Area2d::height);

	register_property<Area2d, godot::Vector2>("bottomLeft", &Area2d::bottomLeft, godot::Vector2());
	register_property<Area2d, godot::Vector2>("topRight", &Area2d::topRight, godot::Vector2());
}