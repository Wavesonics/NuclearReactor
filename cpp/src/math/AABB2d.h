//
// Created by Adam on 2/27/2020.
//

#ifndef REACTORCPPTEST_NEUTRONAREA2D_H
#define REACTORCPPTEST_NEUTRONAREA2D_H

#include <Godot.hpp>
#include <Vector2.hpp>

namespace nuclearPhysics
{
	class AABB2d : public godot::Object
	{
		GODOT_CLASS(AABB2d, godot::Object)
	public:
		godot::Vector2 bottomLeft;
		godot::Vector2 topRight;

		AABB2d();
		AABB2d(const godot::Vector2& bottomLeft, const godot::Vector2& topRight);

		bool contains(const godot::Vector2& point) const;
		float width() const;
		float height() const;

		friend std::ostream &operator<<(std::ostream &os, const AABB2d&a);
		friend std::ostream &operator<<(std::ostream &os, AABB2d&a);

		static void _register_methods();
	};
}

#endif //REACTORCPPTEST_NEUTRONAREA2D_H
