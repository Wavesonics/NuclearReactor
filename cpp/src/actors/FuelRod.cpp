//
// Created by Adam on 2/28/2020.
//

#include "FuelRod.h"
#include "../util/Utils.h"

#include <utility>
#include <iostream>

using namespace std;
using namespace nuclearPhysics;
using namespace godot;


FuelRod::FuelRod() : NeutronRegion()
{
	neutronField = NULL;
}

void FuelRod::_physics_process(float delta)
{
	timeSinceLastFission += delta;
	if(timeSinceLastFission >= SPONTANEUOS_FISION_RATE )
	{
		//cout << "spawn" << endl;
		timeSinceLastFission = 0.0f;
		spawnSpontaneousNeutron();
	}
}

bool FuelRod::handleNeutron(Neutron &neutron)
{
	bool fission = false;
	if(neutron.isThermalized())
	{
		fission = CROSS_SECTION_THERMAL > randPercent();
	}
	else
	{
		fission = CROSS_SECTION_RELATIVISTIC > randPercent();
	}

	if(fission)
	{
		//cout << "fission!" << endl;
		spawnFissionNeutron(neutron);
		spawnFissionNeutron(neutron);
	}

	return fission;
}

void FuelRod::spawnFissionNeutron(Neutron &neutron)
{
	auto velocity = rand_vec2(-1.0f, 1.0f) * Neutron::SPEED_RELATIVISTIC;
	auto newNeutron = Neutron(neutron.position, velocity);
	neutronField->addNeutron(newNeutron);
}

void FuelRod::spawnSpontaneousNeutron()
{
	auto position = rand_vec2(area->bottomLeft.x, area->width(), area->bottomLeft.y, area->height());
	auto velocity = rand_vec2(-1.0f, 1.0f) * Neutron::SPEED_RELATIVISTIC;
	auto newNeutron = Neutron(position, velocity);
	neutronField->addNeutron(newNeutron);
}

FuelRod::~FuelRod() = default;

void FuelRod::_register_methods()
{
	register_method("_physics_process", &FuelRod::_physics_process);
}
