//
// Created by Adam on 2/28/2020.
//

#include "NeutronRegion.h"
#include <utility>

using namespace nuclearPhysics;
using namespace godot;

NeutronRegion::NeutronRegion() : Node2D()
{

}

NeutronRegion::~NeutronRegion() = default;

bool NeutronRegion::contains(const Vector2 &point) const
{
	return area->contains(point);
}

void NeutronRegion::_physics_process(float delta)
{
	
}

void NeutronRegion::_register_methods()
{
	register_property<NeutronRegion, AABB2d*>("area", &NeutronRegion::area, NULL);
	register_method("contains", &NeutronRegion::contains);
	register_method("_physics_process", &NeutronRegion::_physics_process);
}