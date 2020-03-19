//
// Created by Adam on 2/28/2020.
//

#include <iostream>
#include "../../util/Utils.h"
#include "NeutronRegion.h"
#include "../NeutronField/NeutronField.h"
#include "SceneTree.hpp"
#include "Engine.hpp"


using namespace std;
using namespace nuclearPhysics;
using namespace godot;


static const Rect2 DEFAULT_BOUNDS = Rect2(Point2(0.0f, 0.0f), Size2(50, 50));
static const Color DEFAULT_COLOR = Color(0.3, 0.3, 0.3);

NeutronRegion::NeutronRegion() : Node2D()
{

}

NeutronRegion::~NeutronRegion() = default;

bool NeutronRegion::contains(const Vector2 &point) const
{
	const auto localPoint = to_local(point);
	return area.has_point(localPoint);
}

void NeutronRegion::_init()
{
	drawColor = DEFAULT_COLOR;
	area = DEFAULT_BOUNDS;
}

void NeutronRegion::_enter_tree()
{
	// Create our global Rect2 for testing global points
	Vector2 globalAreaPos = get_global_position() + area.position;
	globalArea = Rect2(globalAreaPos, area.size);
}

void NeutronRegion::_ready()
{
	update();
	EDITOR_GUARD_RETURN_HERE

	// Add every neutron region to the neutron field so it can be checked
	auto nodes = get_tree()->get_nodes_in_group(NeutronField::GROUP);
	if (!nodes.empty())
	{
		auto* neutronField = Object::cast_to<NeutronField>(nodes[0]);
		if (neutronField != nullptr)
		{
			neutronField->addNeutronRegion(this);
		}
		else
		{
			Godot::print("FAILED TO GET NEUTRON FIELD!!");
		}
	}
}

void NeutronRegion::_draw()
{
	draw_rect(area, drawColor);
}

void NeutronRegion::_register_methods()
{
	register_property<NeutronRegion, godot::Rect2>("area", &NeutronRegion::area, DEFAULT_BOUNDS);
	register_property<NeutronRegion, godot::Color>("drawColor", &NeutronRegion::drawColor, Color());
	
	register_method("contains", &NeutronRegion::contains);
	register_method("_init", &NeutronRegion::_init);
	register_method("_enter_tree", &NeutronRegion::_enter_tree);
	register_method("_ready", &NeutronRegion::_ready);
	register_method("_draw", &NeutronRegion::_draw);
}
