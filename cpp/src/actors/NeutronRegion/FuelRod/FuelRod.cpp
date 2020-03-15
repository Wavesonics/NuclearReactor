//
// Created by Adam on 2/28/2020.
//

#include "FuelRod.h"
#include "../../../util/Utils.h"
#include <Engine.hpp>
#include <utility>
#include <iostream>

using namespace std;
using namespace nuclearPhysics;
using namespace godot;


static const Rect2 DEFAULT_BOUNDS = Rect2(Point2(0.0f, 0.0f), Size2(20, 200));
static const Color DEFAULT_COLOR = Color(1.0, 0.0, 0.0);

FuelRod::FuelRod() : NeutronRegion()
{
	neutronField = nullptr;
}

void FuelRod::_init()
{
	NeutronRegion::_init();

	drawColor = DEFAULT_COLOR;
	area = DEFAULT_BOUNDS;
}

void FuelRod::_ready()
{
	NeutronRegion::_ready();
	
	add_to_group(GROUP);

	if (Engine::get_singleton()->is_editor_hint()) return;

	neutronField = Object::cast_to<NeutronField>(get_node(neutronFieldPath));
	if (neutronField == nullptr) Godot::print("FUEL ROD FAILED TO GET NEUTRON FIELD!!");

	// Get the thermal map
	thermalMap = Object::cast_to<DiffusingHeatMap>(get_node(thermalMapPath));
	if (thermalMap == nullptr) Godot::print("FAILED TO GET THERMAL MAP!!");
}

void FuelRod::_draw()
{
	NeutronRegion::_draw();
}

void FuelRod::_physics_process(float delta)
{
	if (Engine::get_singleton()->is_editor_hint()) return;

	timeSinceLastFission += delta;
	if (timeSinceLastFission >= SPONTANEUOS_FISION_RATE)
	{
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
		//Godot::print("FISSION!");
		neutronField->addFissionBiproduct(neutron.position);
		neutronField->addHeat(neutron.position, 1.0f);

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
	auto position = rand_vec2(area.position.x, area.size.width, area.position.y, area.size.height);
	auto globalPos = to_global(position);
	auto velocity = rand_vec2(-1.0f, 1.0f) * Neutron::SPEED_RELATIVISTIC;
	auto newNeutron = Neutron(globalPos, velocity);
	neutronField->addNeutron(newNeutron);
}

FuelRod::~FuelRod() = default;

void FuelRod::_register_methods()
{
	register_property<FuelRod, NodePath>("neutronFieldPath", &FuelRod::neutronFieldPath, nullptr);
	register_property<FuelRod, NodePath>("thermalMapPath", &FuelRod::thermalMapPath, nullptr);
	register_property<FuelRod, godot::Color>("drawColor", &FuelRod::drawColor, DEFAULT_COLOR);

	register_method("_init", &FuelRod::_init);
	register_method("_ready", &FuelRod::_ready);
	register_method("_draw", &FuelRod::_draw);
	register_method("_physics_process", &FuelRod::_physics_process);
}