//
// Created by Adam on 3/12/2020.
//

#include "DiffusingHeatMap.h"
#include "../util/Utils.h"
#include <Engine.hpp>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace nuclearPhysics;
using namespace godot;


DiffusingHeatMap::DiffusingHeatMap() : HeatMap()
{
    
}

DiffusingHeatMap::~DiffusingHeatMap() = default;

void DiffusingHeatMap::_init()
{
    HeatMap::_init();
    //mapSize = 16; // Much smaller size as we're running a time intensive algorithm on it
    //cellWidth = 4.0f;
    //cellHeight = 4.0f;
    //drawRectSize = 8.0f;
}

void DiffusingHeatMap::clearBackBuffer()
{
    for (int yy = 0; yy < mapSize; ++yy)
    {
        for (int xx = 0; xx < mapSize; ++xx)
        {
            backBuffer[yy][xx] = 0.0f;
        }
    }
}

void DiffusingHeatMap::_ready()
{
    HeatMap::_ready();

    // Allocate the back buffer
    backBuffer = new float*[mapSize];
    for (int yy = 0; yy < mapSize; ++yy)
    {
        backBuffer[yy] = new float[mapSize];
        for (int xx = 0; xx < mapSize; ++xx)
        {
            backBuffer[yy][xx] = 0.0f;
        }
    }
}

void DiffusingHeatMap::_draw()
{
    HeatMap::_draw();
}

void DiffusingHeatMap::_physics_process(float delta)
{

}

void DiffusingHeatMap::_register_methods()
{
    register_method("_init", &DiffusingHeatMap::_init);
    register_method("_ready", &DiffusingHeatMap::_ready);
    register_method("_physics_process", &DiffusingHeatMap::_physics_process);
    register_method("_draw", &DiffusingHeatMap::_draw);
}
