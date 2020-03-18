//
// Created by Adam on 3/14/2020.
//

#ifndef CPP_THERMOCOUPLE_H
#define CPP_THERMOCOUPLE_H

#include <Godot.hpp>
#include <Node2D.hpp>
#include "../../NeutronField/NeutronField.h"

namespace nuclearPhysics
{
	class Thermocouple : public godot::Node2D
	{
		GODOT_CLASS(Thermocouple, godot::Node2D)
	private:
		godot::Ref<godot::DynamicFont> font;

		godot::Color drawColor;
		float drawRadius;

		NeutronField* neutronField = nullptr;

		float errantReading = NO_ERROR;

		bool enableRendering = DEFAULT_RENDER;
	public:
		Thermocouple();
		~Thermocouple();

		virtual void _init();
		virtual void _ready();
		virtual void _draw();
		virtual void _physics_process(const float delta);

		float readTemperature() const;
		void setErrantReading(const float reading);
		void clearErrantReading();

		static void _register_methods();
		static constexpr float NO_ERROR = -1.0f;
		static constexpr bool DEFAULT_RENDER = true;
	};
}


#endif //CPP_THERMOCOUPLE_H
