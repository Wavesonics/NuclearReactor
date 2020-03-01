//
// Created by Adam on 2/27/2020.
//

#include "Neutron.h"
#include "../util/Utils.h"

#include <iostream>

using namespace std;
using namespace godot;
using namespace nuclearPhysics;

Neutron::Neutron() : position(Vector2()), velocity(Vector2())
{

}

Neutron::Neutron(const Vector2 &position, const Vector2 &velocity)
		: position(position), velocity(velocity)
{
}

bool Neutron::isThermalized() const
{
	const float speed = velocity.length();
	//return about_equal(speed, SPEED_THERMAL, 0.1f);
	return speed <= (SPEED_THERMAL + 1.0f);
}

std::ostream &operator<<(std::ostream &os, const Neutron &n)
{
	os << "Neutron: pos " << n.position << " vel " << n.velocity;
	return os;
}

std::ostream &operator<<(std::ostream &os, Neutron &n)
{
	os << "Neutron: pos " << n.position << " vel " << n.velocity;
	return os;
}
