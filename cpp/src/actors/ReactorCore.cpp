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
    area = DEFAULT_BOUNDS;
}

void ReactorCore::_register_methods()
{
    register_property<ReactorCore, godot::Rect2>("area", &ReactorCore::area, DEFAULT_BOUNDS);
    register_method("_init", &ReactorCore::_init);
}
