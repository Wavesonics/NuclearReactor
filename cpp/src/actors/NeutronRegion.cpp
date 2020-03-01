//
// Created by Adam on 2/28/2020.
//

#include <utility>
#include <iostream>
#include "NeutronRegion.h"
#include "NeutronField.h"
#include "SceneTree.hpp"


using namespace std;
using namespace nuclearPhysics;
using namespace godot;


static const Rect2 DEFAULT_BOUNDS = Rect2(Point2(0.0f, 0.0f), Size2(50, 50));

NeutronRegion::NeutronRegion() : Node2D()
{

}

NeutronRegion::~NeutronRegion() = default;

bool NeutronRegion::contains(const Vector2 &point) const
{
	return globalArea.has_point(point);
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
	Vector2 globalAreaPos = get_global_position() + area.position;
	globalArea = Rect2(globalAreaPos, area.size);
	update();

	// Add every neutron region to the neutron field so it can be checked
	auto nodes = get_tree()->get_nodes_in_group("neutron_field");
	if (nodes.size() > 0)
	{
		NeutronField* neutronField = Object::cast_to<NeutronField>(nodes[0]);
		if (neutronField != nullptr)
		{
			cout << "adding NR to NF" << endl;
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
	register_method("_ready", &NeutronRegion::_ready);
	register_method("_draw", &NeutronRegion::_draw);
}