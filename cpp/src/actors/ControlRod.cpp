//
// Created by Adam on 2/28/2020.
//

#include "ControlRod.h"
#include "../util/Utils.h"
#include <utility>

using namespace nuclearPhysics;
using namespace godot;

static const Rect2 DEFAULT_BOUNDS = Rect2(Point2(0.0f, 0.0f), Size2(20, 200));
static const Color DEFAULT_COLOR = Color(0.0, 1.0, 0.0);

ControlRod::ControlRod() : NeutronRegion()
{

}

void ControlRod::_init()
{
    NeutronRegion::_init();

    drawColor = DEFAULT_COLOR;
    area = DEFAULT_BOUNDS;
}

void ControlRod::_ready()
{
    NeutronRegion::_ready();

    add_to_group("control_rod");
}

void ControlRod::_draw()
{
    NeutronRegion::_draw();
}

bool ControlRod::handleNeutron(Neutron &neutron)
{
	return CROSS_SECTION > randPercent();
}

ControlRod::~ControlRod() = default;

void ControlRod::_register_methods()
{
    register_property<ControlRod, godot::Color>("drawColor", &ControlRod::drawColor, DEFAULT_COLOR);

    register_method("_init", &ControlRod::_init);
    register_method("_ready", &ControlRod::_ready);
    register_method("_draw", &ControlRod::_draw);
}