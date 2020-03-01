//
// Created by Adam on 2/28/2020.
//

#include "NeutronRegion.h"
#include <utility>

using namespace nuclearPhysics;
using namespace godot;

static const Rect2 DEFAULT_BOUNDS = Rect2(Point2(0.0f, 0.0f), Size2(50, 50));

NeutronRegion::NeutronRegion() : Node2D()
{

}

NeutronRegion::~NeutronRegion() = default;

bool NeutronRegion::contains(const Vector2 &point) const
{
	return area.has_point(point);
}

void NeutronRegion::_init()
{
	drawColor = Color();
	drawColor.a = 1.0f;
	drawColor.r = 0.0f;
	drawColor.g = 0.0f;
	drawColor.b = 0.0f;

	area = DEFAULT_BOUNDS;
}

void NeutronRegion::_ready()
{
	update();
}

void NeutronRegion::_draw()
{
	Godot::print("NeutronRegion::_draw()");
	draw_rect(area, drawColor);
}

void NeutronRegion::_register_methods()
{
	register_property<NeutronRegion, godot::Rect2>("area", &NeutronRegion::area, DEFAULT_BOUNDS);
	register_method("contains", &NeutronRegion::contains);
	register_method("_init", &NeutronRegion::_init);
	register_method("_ready", &NeutronRegion::_ready);
	register_method("_draw", &NeutronRegion::_draw);
}