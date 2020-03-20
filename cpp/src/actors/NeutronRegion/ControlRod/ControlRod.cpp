//
// Created by Adam on 2/28/2020.
//

#include "ControlRod.h"
#include "../../../util/Utils.h"
#include <cmath>
#include <algorithm>
#include <Engine.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>
#include <Variant.hpp>

using namespace std;
using namespace nuclearPhysics;
using namespace godot;

static const Rect2 DEFAULT_BOUNDS = Rect2(Point2(0.0f, 0.0f), Size2(20, 200));
static const Color DEFAULT_COLOR = Color(0.0, 1.0, 0.0);
static constexpr float DEFAULT_CUR_POS = 0.0f;

ControlRod::ControlRod() : NeutronRegion()
{

}

void ControlRod::_init()
{
    NeutronRegion::_init();

    drawColor = DEFAULT_COLOR;
    area = DEFAULT_BOUNDS;

    fullOutPositionDelta = 0.0f;
    fullInPosition = 0.0f;
    currentPositionDelta = 0.0f;
    initialPercentOut = 0.0f;

    speed = SPEED;
    scramSpeed = SPEED_SCRAM;
}

void ControlRod::_enter_tree()
{
	NeutronRegion::_enter_tree();
}

void ControlRod::_ready()
{
    NeutronRegion::_ready();

	EDITOR_GUARD_RETURN_HERE

	add_to_group(GROUP);

    fullOutPositionDelta = area.size.height;
    fullInPosition = get_position().y;
    currentPositionDelta = (-fabs(fullOutPositionDelta * initialPercentOut));
    updatePosition();

    // Each control rod adds it's self to the global ControlSystem
    Node* obj = get_tree()->get_root()->find_node("ControlSystem", true, false);
    if (obj != nullptr)
    {
        obj->call("add_control_rod", Variant(this));
    }
    else
    {
        Godot::print("Failed to get ControlSystem");
    }
}

void ControlRod::_draw()
{
    NeutronRegion::_draw();
}

bool ControlRod::handleNeutron(Neutron &neutron, const Vector2 &globalPosition)
{
	return CROSS_SECTION > randPercent();
}

float ControlRod::percentOut() const
{
    const float totalDistance = fabs(fullOutPositionDelta);
    const float curPos = fabs(currentPositionDelta);

    if (curPos > 0.0f)
    {
        return curPos / totalDistance;
    }
    else
    {
        return 0.0f;
    }
}

void ControlRod::moveOut(float delta, float speed = SPEED)
{
    currentPositionDelta -= speed * delta;
    updatePosition();
}

void ControlRod::moveIn(float delta, float speed = SPEED)
{
    currentPositionDelta += speed * delta;
    updatePosition();
}

void ControlRod::updatePosition()
{
	EDITOR_GUARD_RETURN_HERE

    currentPositionDelta = clamp(currentPositionDelta, -fullOutPositionDelta, 0.0f);
    
    Vector2 pos = get_position();
    pos.y = fullInPosition + currentPositionDelta;
    set_position(pos);

    // Now update our cached rect used for checking
    Vector2 globalAreaPos = get_position() + area.position;
    globalArea = Rect2(globalAreaPos, area.size);
}

ControlRod::~ControlRod() = default;

void ControlRod::_register_methods()
{
    register_property<ControlRod, godot::Color>("drawColor", &ControlRod::drawColor, DEFAULT_COLOR);
    register_property<ControlRod, float>("initialPercentOut", &ControlRod::initialPercentOut, DEFAULT_CUR_POS);
    register_property<ControlRod, float>("speed", &ControlRod::speed, SPEED);
    register_property<ControlRod, float>("scramSpeed", &ControlRod::scramSpeed, SPEED_SCRAM);
    
    register_method("percent_out", &ControlRod::percentOut);
    register_method("move_out", &ControlRod::moveOut);
    register_method("move_in", &ControlRod::moveIn);
    
    register_method("_init", &ControlRod::_init);
	register_method("_enter_tree", &ControlRod::_enter_tree);
    register_method("_ready", &ControlRod::_ready);
    register_method("_draw", &ControlRod::_draw);
}
