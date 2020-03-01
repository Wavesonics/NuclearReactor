//
// Created by Adam on 2/27/2020.
//

#include "ReactorCore.h"
#include "../util/Utils.h"
#include <iostream>

using namespace std;
using namespace nuclearPhysics;
using namespace godot;

static const Rect2 DEFAULT_BOUNDS = Rect2(Point2(0.0f, 0.0f), Size2(100.0f, 100.0f));
static const Color DEFAULT_COLOR = Color(0.0, 0.0, 0.0);

ReactorCore::ReactorCore() : NeutronRegion()
{

}

ReactorCore::~ReactorCore() = default;

bool ReactorCore::handleNeutron(Neutron & neutron)
{
    return false;
}

void ReactorCore::_init()
{
    NeutronRegion::_init();
    area = DEFAULT_BOUNDS;
    drawColor = DEFAULT_COLOR;
}

void ReactorCore::_ready()
{
    NeutronRegion::_ready();
}

void ReactorCore::_draw()
{
    NeutronRegion::_draw();
}

void ReactorCore::_register_methods()
{
    register_property<ReactorCore, godot::Rect2>("area", &ReactorCore::area, DEFAULT_BOUNDS);
    register_property<ReactorCore, godot::Color>("drawColor", &ReactorCore::drawColor, DEFAULT_COLOR);

    register_method("_init", &ReactorCore::_init);
    register_method("_ready", &ReactorCore::_ready);
    register_method("_draw", &ReactorCore::_draw);
}
