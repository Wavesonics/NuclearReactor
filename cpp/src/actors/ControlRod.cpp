//
// Created by Adam on 2/28/2020.
//

#include "ControlRod.h"
#include "../util/Utils.h"
#include <utility>

using namespace nuclearPhysics;

ControlRod::ControlRod() : NeutronRegion()
{

}

void ControlRod::_physics_process(float delta)
{
	// No-op
}

bool ControlRod::handleNeutron(Neutron &neutron)
{
	return CROSS_SECTION > randPercent();
}

ControlRod::~ControlRod() = default;

void ControlRod::_register_methods()
{
	register_method("_physics_process", &ControlRod::_physics_process);
}