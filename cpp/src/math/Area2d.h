//
// Created by Adam on 2/27/2020.
//

#ifndef REACTORCPPTEST_AREA2D_H
#define REACTORCPPTEST_AREA2D_H

#include <Godot.hpp>
#include <Vector2.hpp>

namespace nuclearPhysics
{
	class Area2d : public godot::Object
	{
		GODOT_CLASS(Area2d, godot::Object)
	public:
		godot::Vector2 bottomLeft;
		godot::Vector2 topRight;

		Area2d();
		Area2d(const godot::Vector2&bottomLeft, const godot::Vector2& topRight);

		bool contains(const godot::Vector2&point) const;
		float width() const;
		float height() const;

		friend std::ostream &operator<<(std::ostream &os, const Area2d &a);
		friend std::ostream &operator<<(std::ostream &os, Area2d &a);

		static void _register_methods();
	};
}

#endif //REACTORCPPTEST_AREA2D_H
