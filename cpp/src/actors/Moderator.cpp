//
// Created by Adam on 2/27/2020.
//

#include "Moderator.h"
#include "../util/Utils.h"
#include <iostream>

using namespace std;
using namespace nuclearPhysics;
using namespace godot;


Moderator::Moderator() : NeutronRegion()
{

}

Moderator::~Moderator() = default;

void Moderator::_physics_process(float delta)
{
    // No-op
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
    register_method("_physics_process", &Moderator::_physics_process);
}
