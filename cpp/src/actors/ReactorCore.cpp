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
    coreBounds = DEFAULT_BOUNDS;
}

void ReactorCore::_ready()
{
    cout << "pos " << coreBounds.position.x << ", " << coreBounds.position.y << " size " << coreBounds.size.width << ", " << coreBounds.size.width << endl;
    area = new AABB2d(Vector2(coreBounds.position.x, coreBounds.position.y), Vector2(coreBounds.position.x + coreBounds.size.width, coreBounds.position.y + coreBounds.size.height));
    cout << "bottomLeft " << area->bottomLeft.x << ", " << area->bottomLeft.y << " topRight " << area->topRight.x << ", " << area->topRight.y << endl;
}

void ReactorCore::_draw()
{
    Godot::print("_draw");
    auto color = Color();
    color.a = 1.0f;
    color.r = 0.0f;
    color.g = 0.0f;
    color.b = 0.0f;

    draw_rect(coreBounds, color);
    Godot::print("_draw DONE");
}

void ReactorCore::_register_methods()
{
    register_property<ReactorCore, Rect2>("coreBounds", &ReactorCore::coreBounds, DEFAULT_BOUNDS);
    register_method("_init", &ReactorCore::_init);
    register_method("_ready", &ReactorCore::_ready);
}
