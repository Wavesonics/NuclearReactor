//
// Created by Adam on 2/27/2020.
//

#include "AABB2d.h"
#include "../util/Utils.h"

using namespace nuclearPhysics;
using namespace godot;

AABB2d::AABB2d() : bottomLeft(Vector2()), topRight(Vector2())
{

}

AABB2d::AABB2d(const godot::Vector2 &bottomLeft, const godot::Vector2 &topRight)
		: bottomLeft(bottomLeft), topRight(topRight)
{
}

bool AABB2d::contains(const godot::Vector2 &point) const
{
	return point.x > bottomLeft.x && point.x < topRight.x && point.y > bottomLeft.y && point.y < topRight.y;
}

float AABB2d::width() const
{
	return topRight.x - bottomLeft.x;
}

float AABB2d::height() const
{
	return topRight.y - bottomLeft.y;
}

std::ostream &operator<<(std::ostream &os, const AABB2d &a)
{
	os << "Bottom Left" << a.bottomLeft << " Top Right: " << a.topRight << ")";
	return os;
}

std::ostream &operator<<(std::ostream &os, AABB2d &a)
{
	os << "Bottom Left" << a.bottomLeft << " Top Right: " << a.topRight << ")";
	return os;
}

void AABB2d::_register_methods()
{
	register_method("contains", &AABB2d::contains);
	register_method("width", &AABB2d::width);
	register_method("height", &AABB2d::height);

	register_property<AABB2d, godot::Vector2>("bottomLeft", &AABB2d::bottomLeft, godot::Vector2());
	register_property<AABB2d, godot::Vector2>("topRight", &AABB2d::topRight, godot::Vector2());
}