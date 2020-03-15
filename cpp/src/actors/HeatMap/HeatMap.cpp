//
// Created by Adam on 2/27/2020.
//

#include "HeatMap.h"
#include "../../util/Utils.h"
#include <Engine.hpp>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace nuclearPhysics;
using namespace godot;


HeatMap::HeatMap() : Node2D()
{

}

HeatMap::~HeatMap() = default;

void HeatMap::calculateCellSizes(const godot::Rect2 &rect)
{
	cellWidth = rect.size.width / (float) mapSize;
	cellHeight = rect.size.height / (float) mapSize;
}

bool HeatMap::rangeCheck(const int x, const int y) const
{
	return x >= 0 && x < mapSize && y >= 0 && y < mapSize;
}

void HeatMap::addHeat(float heat, const int x, const int y)
{
	if(rangeCheck(x, y))
	{
		map[y][x] = clamp(map[y][x] + heat, 0.0f, maxValue);
	}
	else
	{
		Godot::print("HeatMap:: index out of range {0}, {1} | {2}", x, y, mapSize);
	}
}

float HeatMap::readMagnitude(const int x, const int y) const
{
	if(rangeCheck(x, y))
	{
		return map[y][x];
	}
	else
	{
		return -1.0f;
	}
}


void HeatMap::_init()
{
	mapSize = DEFAULT_MAP_SIZE;
	enableRendering = true;
	drawRectSize = DEFAULT_DRAW_SIZE;
}

void HeatMap::_ready()
{
	map = new float *[mapSize];
	for(int yy = 0; yy < mapSize; ++yy)
	{
		map[yy] = new float[mapSize];
		for(int xx = 0; xx < mapSize; ++xx)
		{
			map[yy][xx] = 0.0f;
		}
	}
}

void HeatMap::_draw()
{
	if(!enableRendering) return;

	auto drawRect = Rect2(Vector2(), Vector2(drawRectSize, drawRectSize));

	for(int yy = 0; yy < mapSize; ++yy)
	{
		drawRect.position.y = yy * drawRectSize;

		for(int xx = 0; xx < mapSize; ++xx)
		{
			//const float heat = map[yy][xx] / maxValue;

			drawRect.position.x = xx * drawRectSize;
			//color.r = heat;

			draw_rect(drawRect, calculateTempColor(map[yy][xx], minValue, maxValue));
		}
	}
}

godot::Color HeatMap::calculateTempColor(const float value, const float minimum, const float maximum) const
{
	if(value < minimum)
	{
		return Color();
	}
	else
	{
		const float halfmax = (maximum - minimum) / 2.0f;
		const float b = max(0.0f, (1.0f - (value - minimum) / halfmax));
		const float r = max(0.0f, ((value - minimum) / halfmax - 1));
		const float g = 1.0f - b - r;
		return Color(r, g, b);
	}
}

void HeatMap::_register_methods()
{
	register_property<HeatMap, int>("mapSize", &HeatMap::mapSize, DEFAULT_MAP_SIZE);
	register_property<HeatMap, float>("drawRectSize", &HeatMap::drawRectSize, DEFAULT_DRAW_SIZE);
	register_property<HeatMap, bool>("enableRendering", &HeatMap::enableRendering, true);

	register_method("add_heat", &HeatMap::addHeat);
	register_method("read_magnitude", &HeatMap::readMagnitude);
	register_method("_init", &HeatMap::_init);
	register_method("_ready", &HeatMap::_ready);
	register_method("_draw", &HeatMap::_draw);
}