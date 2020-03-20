//
// Created by Adam on 2/27/2020.
//

#include "Moderator.h"
#include "../../../util/Utils.h"
#include <Engine.hpp>
#include <iostream>

using namespace std;
using namespace nuclearPhysics;
using namespace godot;


static const Rect2 DEFAULT_BOUNDS = Rect2(Point2(0.0f, 0.0f), Size2(40, 200));
static const Color DEFAULT_COLOR = Color(0.0, 0.0, 0.5);


Moderator::Moderator() : NeutronRegion()
{

}

Moderator::~Moderator() = default;

void Moderator::_init()
{
    NeutronRegion::_init();

    drawColor = DEFAULT_COLOR;
    area = DEFAULT_BOUNDS;
}

void Moderator::_enter_tree()
{
	NeutronRegion::_enter_tree();
}

void Moderator::_ready()
{
    NeutronRegion::_ready();

	EDITOR_GUARD_RETURN_HERE

    add_to_group(GROUP);
}

void Moderator::_draw()
{
    NeutronRegion::_draw();
}

bool Moderator::handleNeutron(Neutron &neutron, const Vector2 &globalPosition)
{
    if(!neutron.isThermalized())
    {
        if(CROSS_SECTION_RELATIVISTIC > randPercent())
        {
        	const float MAX_ANGLE = 0.45;
            auto reflected = neutron.velocity.normalized() * -1.0f;
            reflected.x += randf(-MAX_ANGLE, MAX_ANGLE);
            reflected.y += randf(-MAX_ANGLE, MAX_ANGLE);

            neutron.velocity = reflected.normalized() * Neutron::SPEED_THERMAL;
        }
    }

    return false;
}

void Moderator::_register_methods()
{
    register_property<Moderator, godot::Color>("drawColor", &Moderator::drawColor, DEFAULT_COLOR);

    register_method("_init", &Moderator::_init);
	register_method("_enter_tree", &Moderator::_enter_tree);
    register_method("_ready", &Moderator::_ready);
    register_method("_draw", &Moderator::_draw);
}
