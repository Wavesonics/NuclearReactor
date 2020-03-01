//
// Created by Adam on 2/27/2020.
//

#include "Moderator.h"
#include "../util/Utils.h"
#include <iostream>

using namespace std;
using namespace nuclearPhysics;
using namespace godot;


static const Rect2 DEFAULT_BOUNDS = Rect2(Point2(0.0f, 0.0f), Size2(40, 200));

Moderator::Moderator() : NeutronRegion()
{

}

Moderator::~Moderator() = default;

void Moderator::_init()
{
    NeutronRegion::_init();

    drawColor = Color();
    drawColor.a = 1.0f;
    drawColor.r = 0.0f;
    drawColor.g = 0.0f;
    drawColor.b = 0.5f;

    area = DEFAULT_BOUNDS;
}

void Moderator::_ready()
{
    NeutronRegion::_ready();

    add_to_group("fuel_rod");
}

void Moderator::_draw()
{
    NeutronRegion::_draw();
}

bool Moderator::handleNeutron(Neutron &neutron)
{
    if(!neutron.isThermalized())
    {
        if(CROSS_SECTION_RELATIVISTIC > randPercent())
        {
            auto reflected = neutron.velocity.normalized() * -1.0f;
            reflected.x += randf(-0.25f, 0.25f);
            reflected.y += randf(-0.25f, 0.25f);

            neutron.velocity = reflected.normalized() * Neutron::SPEED_THERMAL;
        }
    }

    return false;
}

void Moderator::_register_methods()
{
    register_method("_init", &Moderator::_init);
    register_method("_ready", &Moderator::_ready);
    register_method("_draw", &Moderator::_draw);
}
