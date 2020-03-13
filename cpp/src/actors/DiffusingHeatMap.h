//
// Created by Adam on 2/27/2020.
//

#ifndef REACTORCPP_DIFFUSING_HEATMAP_H
#define REACTORCPP_DIFFUSING_HEATMAP_H

#include "HeatMap.h"
#include <Godot.hpp>
#include <Node2D.hpp>

namespace nuclearPhysics
{
	class DiffusingHeatMap : public HeatMap
	{
		GODOT_CLASS(DiffusingHeatMap, nuclearPhysics::HeatMap)
	private:
		float** backBuffer;
		float** currentMap;

		void clearBackBuffer();
	public:

		DiffusingHeatMap();
		~DiffusingHeatMap();

		virtual void _init();
		virtual void _ready();
		virtual void _physics_process(float delta);
		virtual void _draw();

		static void _register_methods();
	};
}

#endif //REACTORCPP_DIFFUSING_HEATMAP_H
