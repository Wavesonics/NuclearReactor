//
// Created by Adam on 3/14/2020.
//

#ifndef CPP_THERMOCOUPLE_H
#define CPP_THERMOCOUPLE_H

#include <Godot.hpp>
#include <Node2D.hpp>

namespace nuclearPhysics
{
	class Thermocouple : public godot::Node2D
	{
		GODOT_CLASS(Thermocouple, godot::Node2D)
	private:
		godot::Color drawColor;
		float drawRadius;
	public:
		Thermocouple();
		~Thermocouple();

		virtual void _init();
		virtual void _ready();
		virtual void _draw();

		static void _register_methods();
	};
}


#endif //CPP_THERMOCOUPLE_H
