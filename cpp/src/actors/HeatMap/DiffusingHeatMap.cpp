//
// Created by Adam on 3/12/2020.
//

#include <algorithm>
#include <cmath>
#include <Ref.hpp>
#include <Font.hpp>
#include <InputEvent.hpp>
#include "DiffusingHeatMap.h"

using namespace std;
using namespace nuclearPhysics;
using namespace godot;

constexpr float MIN_HEAT = 0.1f;

DiffusingHeatMap::DiffusingHeatMap() : HeatMap()
{

}

DiffusingHeatMap::~DiffusingHeatMap() = default;

void DiffusingHeatMap::_init()
{
	HeatMap::_init();
	mapSize = DEFAULT_MAP_SIZE; // Much smaller size as we're running a time intensive algorithm on it
	drawRectSize = DEFAULT_DRAW_SIZE;
	minValue = 1.0f;
	maxValue = 100.0f;
	diffusionTickRateSeconds = DEFAULT_TICK_RATE_SECONDS;
}

void DiffusingHeatMap::clearBackBuffer()
{
	for(int yy = 0; yy < mapSize; ++yy)
	{
		memset(backBuffer[yy], 0.0f, sizeof(float) * mapSize);
	}
}

void DiffusingHeatMap::swapBackBuffer()
{
	swap(map, backBuffer);
}

void DiffusingHeatMap::_ready()
{
	HeatMap::_ready();

	//set_process_input(true);
	//ResourceLoader *reLo = ResourceLoader::get_singleton();
	//fontRes = Ref<DynamicFont>(reLo->load("res://vr/debug_font.tres"));

	// Allocate the back buffer
	backBuffer = new float *[mapSize];
	for(int yy = 0; yy < mapSize; ++yy)
	{
		backBuffer[yy] = new float[mapSize];
		for(int xx = 0; xx < mapSize; ++xx)
		{
			backBuffer[yy][xx] = 0.0f;
		}
	}
}

/*
void DiffusingHeatMap::_input(const Ref<InputEvent> event)
{
	if(event->is_action_released("advance_heat"))
	{
		debugAdvance = true;
	}
}
 */

void DiffusingHeatMap::_draw()
{
	HeatMap::_draw();

	/*
	if(!enableRendering) return;

	const float lineHeight = fontRes->get_height();
	for(int yy = 0; yy < mapSize; ++yy)
	{
		for(int xx = 0; xx < mapSize; ++xx)
		{
			//const float heat = map[yy][xx] / maxValue;

			float heat = map[yy][xx];
			auto str = godot::String::num(heat, 1);

			Vector2 pos = Vector2(xx * drawRectSize, (yy * drawRectSize) + lineHeight);
			draw_string(fontRes, pos, str, Color(0.2f, 0.8f, 0.2f));
		}
	}
	*/
}

void DiffusingHeatMap::_physics_process(const float delta)
{
	timeSinceLastDiffusion += delta;
	if(timeSinceLastDiffusion >= diffusionTickRateSeconds)
	//if(debugAdvance)
	{
		debugAdvance = false;
		timeSinceLastDiffusion = 0.0f;

		clearBackBuffer();

		for(int yy = 0; yy < mapSize; ++yy)
		{
			for(int xx = 0; xx < mapSize; ++xx)
			{
				diffuse(xx, yy);
			}
		}

		swapBackBuffer();

		update();
	}
}

void DiffusingHeatMap::diffuse(int x, int y)
{
	// Control if we diffuse on all side, or just up/down/left/right
	constexpr bool cardinalDiffusion = true;
	float DIVISOR; // The number of sides it can defuse to
	if(cardinalDiffusion)
	{
		DIVISOR = 5.0f;
	}
	else
	{
		DIVISOR = 9.0f;
	}

	const float heat = map[y][x];
	const float diffuse = heat / DIVISOR;

	float amountDiffused = 0.0f;

	if(diffuse > (MIN_HEAT * DIVISOR))
	{
		// Top Left
		if(!cardinalDiffusion) amountDiffused += diffuseToCell(x - 1, y - 1, heat, diffuse);
		// Top Center
		amountDiffused += diffuseToCell(x, y - 1, heat, diffuse);
		// Top Right
		if(!cardinalDiffusion) amountDiffused += diffuseToCell(x + 1, y - 1, heat, diffuse);

		// Center Left
		amountDiffused += diffuseToCell(x - 1, y, heat, diffuse);
		// Center Right
		amountDiffused += diffuseToCell(x + 1, y, heat, diffuse);

		// Bottom Left
		if(!cardinalDiffusion) amountDiffused += diffuseToCell(x - 1, y + 1, heat, diffuse);
		// Bottom Center
		amountDiffused += diffuseToCell(x, y + 1, heat, diffuse);
		// Bottom Right
		if(!cardinalDiffusion) amountDiffused += diffuseToCell(x + 1, y + 1, heat, diffuse);
	}

	// Set the new value for this voxel
	// We subtract all of the heat that was diffused to other cells
	backBuffer[y][x] += (heat - amountDiffused);
}

float DiffusingHeatMap::diffuseToCell(int x, int y, float heat, float diffuse)
{
	float diffused = 0.0f;

	if(rangeCheck(x, y) && isless(map[y][x], heat-minValue) && isless(backBuffer[y][x], heat-minValue))
	{
		float ratio = (heat - map[y][x]) / heat;
		float amountToDiffuse = diffuse * ratio;

		backBuffer[y][x] += amountToDiffuse;
		diffused = amountToDiffuse;
	}

	return diffused;
}

void DiffusingHeatMap::_register_methods()
{
	register_property<DiffusingHeatMap, int>("mapSize", &DiffusingHeatMap::mapSize, DEFAULT_MAP_SIZE);
	register_property<DiffusingHeatMap, float>("drawRectSize", &DiffusingHeatMap::drawRectSize, DEFAULT_DRAW_SIZE);
	register_property<DiffusingHeatMap, bool>("enableRendering", &DiffusingHeatMap::enableRendering, true);
	register_property<DiffusingHeatMap, float>("diffusionTickRateSeconds", &DiffusingHeatMap::diffusionTickRateSeconds,
											   DEFAULT_TICK_RATE_SECONDS);

	register_method("read_magnitude", &DiffusingHeatMap::readMagnitude);
	register_method("_init", &DiffusingHeatMap::_init);
	register_method("_ready", &DiffusingHeatMap::_ready);
	register_method("_physics_process", &DiffusingHeatMap::_physics_process);
	register_method("_draw", &DiffusingHeatMap::_draw);
	//register_method("_input", &DiffusingHeatMap::_input);
}
