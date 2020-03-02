//
// Created by Adam on 2/27/2020.
//

#ifndef REACTORCPP_NEUTRON_H
#define REACTORCPP_NEUTRON_H

#include <iostream>
#include <Vector2.hpp>

namespace nuclearPhysics
{
	class Neutron
	{
	public:
		godot::Vector2 position;
		godot::Vector2 velocity;

		Neutron();

		Neutron(const godot::Vector2 &position, const godot::Vector2 &velocity);

		bool isThermalized() const;

		static constexpr float SPEED_THERMAL = 50.0f;
		static constexpr float SPEED_RELATIVISTIC = 200.0f;

		friend std::ostream &operator<<(std::ostream &os, const Neutron &n);
		friend std::ostream &operator<<(std::ostream &os, Neutron &n);
	};
}

#endif //REACTORCPP_NEUTRON_H
