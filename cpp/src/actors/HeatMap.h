//
// Created by Adam on 2/27/2020.
//

#ifndef REACTORCPP_HEATMAP_H
#define REACTORCPP_HEATMAP_H


#include <Godot.hpp>
#include <Node2D.hpp>

namespace nuclearPhysics
{
	class HeatMap : public godot::Node2D
	{
	GODOT_CLASS(HeatMap, godot::Node2D)
	private:
		inline godot::Color calculateTempColor(const float value, const float min, const float max) const;
	protected:
		bool enableRendering = true;
		float minValue = 0.01f;
		float maxValue = 1.0f;
		float drawRectSize;
	public:
		int mapSize = DEFAULT_MAP_SIZE;
		float cellWidth = 1.0f;
		float cellHeight = 1.0f;
		float **map;

		HeatMap();

		~HeatMap();

		void calculateCellSizes(const godot::Rect2 &rect);

		void addHeat(float heat, const int x, const int y);

		virtual void _init();

		virtual void _ready();

		virtual void _draw();

		static void _register_methods();

		static constexpr int DEFAULT_MAP_SIZE = 64;
		static constexpr int DEFAULT_DRAW_SIZE = 2.0f;
	};
}

#endif //REACTORCPP_HEATMAP_H
