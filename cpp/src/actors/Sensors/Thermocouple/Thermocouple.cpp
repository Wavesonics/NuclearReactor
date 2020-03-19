//
// Created by Adam on 3/14/2020.
//

#include "Thermocouple.h"
#include "../../../util/Utils.h"
#include <Engine.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>
#include <Variant.hpp>

using namespace nuclearPhysics;
using namespace godot;

Thermocouple::Thermocouple() = default;

Thermocouple::~Thermocouple() = default;

void Thermocouple::_init()
{
	drawColor = Color(0.8f, 0.2f, 0.0f);
	drawRadius = 8.0f;
	enableRendering = DEFAULT_RENDER;

	font = Ref<DynamicFont>();
}

void Thermocouple::_ready()
{
	update();

	EDITOR_GUARD_RETURN_HERE

	add_to_group("thermocouples");

	Node* obj = get_tree()->get_root()->find_node("ControlSystem", true, false);
	if (obj != nullptr)
	{
		// Each control rod adds it's self to the global ControlSystem
		neutronField = Object::cast_to<NeutronField>(obj->call("get_neutron_field"));
		obj->call("add_thermocouple", Variant(this));
	}
	else
	{
		Godot::print("Thermocouple: Failed to get ControlSystem");
	}
}

void Thermocouple::_draw()
{
	if(!enableRendering) return;

	const float negHalfR = -(drawRadius / 2.0f);
	const Point2 pos = Vector2(negHalfR, negHalfR);
	draw_circle(pos, drawRadius, drawColor);

	if(font.is_valid())
	{
		if (!Engine::get_singleton()->is_editor_hint())
		{
			float reading = readTemperature();
			draw_string(font, Point2(-drawRadius, negHalfR), String::num(reading, 1));
		}
	}
}

void Thermocouple::_physics_process(const float delta)
{
	EDITOR_GUARD_RETURN_HERE

	if(enableRendering)
	{
		lastDraw += delta;
		if(lastDraw < DRAW_INTERVAL)
		{
			lastDraw = 0.0f;
			update();
		}
	}
}

float Thermocouple::readTemperature() const
{
	if(errantReading > NO_ERROR)
	{
		return errantReading;
	}
	else
	{
		return neutronField->readHeat(get_global_position());
	}
}

void Thermocouple::setErrantReading(const float reading)
{
	errantReading = reading;
}

void Thermocouple::clearErrantReading()
{
	errantReading = NO_ERROR;
}

void Thermocouple::_register_methods()
{
	register_property<Thermocouple, Ref<DynamicFont>>("font", &Thermocouple::font, nullptr);
	register_property<Thermocouple, bool>("enableRendering", &Thermocouple::enableRendering, DEFAULT_RENDER);

	register_method("read_temperature", &Thermocouple::readTemperature);
	register_method("set_errant_reading", &Thermocouple::setErrantReading);
	register_method("clear_errant_reading", &Thermocouple::clearErrantReading);

	register_method("_init", &Thermocouple::_init);
	register_method("_ready", &Thermocouple::_ready);
	register_method("_draw", &Thermocouple::_draw);
	register_method("_physics_process", &Thermocouple::_physics_process);
}
