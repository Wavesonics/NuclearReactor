//
// Created by Adam on 3/14/2020.
//

#include "Thermocouple.h"

using namespace nuclearPhysics;
using namespace godot;

Thermocouple::Thermocouple() = default;

Thermocouple::~Thermocouple() = default;

void Thermocouple::_init()
{
	drawColor = Color(0.8f, 0.2f, 0.0f);
	drawRadius = 8.0f;
}

void Thermocouple::_ready()
{
	update();
}

void Thermocouple::_draw()
{
	draw_circle(get_position(), drawRadius, drawColor);
}

void Thermocouple::_register_methods()
{
	register_method("_init", &Thermocouple::_init);
	register_method("_ready", &Thermocouple::_ready);
	register_method("_draw", &Thermocouple::_draw);
}