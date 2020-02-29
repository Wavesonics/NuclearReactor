//
// Created by Adam on 2/28/2020.
//

#include "Utils.h"


float randf(const float min, const float max)
{
	return min + (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max-min))));
}

float randPercent()
{
	return randf(0.0f, 1.0f);
}

godot::Vector2 rand_vec2(const float start, const float range)
{
	return godot::Vector2(randf(start, range), randf(start, range));
}

godot::Vector2 rand_vec2(const float startX, const float rangeX, const float startY, const float rangeY)
{
	return godot::Vector2(randf(startX, rangeX), randf(startY, rangeY));
}

bool about_equal(float a, float b, float epsilon)
{
	return (a - b) <= epsilon;
}

std::ostream& operator<<(std::ostream& os, const godot::Vector2& v)
{
	os << "(" << v.x << ", " << v.y << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, godot::Vector2& v)
{
	os << "(" << v.x << ", " << v.y << ")";
	return os;
}