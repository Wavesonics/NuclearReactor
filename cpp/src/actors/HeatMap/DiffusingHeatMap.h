//
// Created by Adam on 2/27/2020.
//

#ifndef REACTORCPP_DIFFUSING_HEATMAP_H
#define REACTORCPP_DIFFUSING_HEATMAP_H

#include "HeatMap.h"
#include <Godot.hpp>
#include <Node2D.hpp>
#include <DynamicFont.hpp>

namespace nuclearPhysics
{
	class DiffusingHeatMap : public HeatMap
	{
	GODOT_CLASS(DiffusingHeatMap, nuclearPhysics::HeatMap)
	private:
		// Debugging
		//godot::Ref<godot::DynamicFont> fontRes;
		bool debugAdvance = false;

		float **backBuffer;
		float timeSinceLastDiffusion = 0.0f;
		float diffusionTickRateSeconds = DEFAULT_TICK_RATE_SECONDS;

		void clearBackBuffer();

		void swapBackBuffer();

		void diffuse(int x, int y);

		inline float diffuseToCell(int x, int y, float heat, float diffuse);

	public:

		DiffusingHeatMap();

		~DiffusingHeatMap();

		void _init() override;

		void _ready() override;

		virtual void _physics_process(const float delta);

		void _draw() override;

		//virtual void _input(const godot::Ref<godot::InputEvent> event);

		static void _register_methods();

		static constexpr int DEFAULT_MAP_SIZE = 32;
		static constexpr int DEFAULT_DRAW_SIZE = 4.0f;
		static constexpr int DEFAULT_TICK_RATE_SECONDS = 1.0f;
	};
}

#endif //REACTORCPP_DIFFUSING_HEATMAP_H
