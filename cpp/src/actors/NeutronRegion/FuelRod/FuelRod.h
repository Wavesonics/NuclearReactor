//
// Created by Adam on 2/28/2020.
//

#ifndef REACTORCPP_FUELROD_H
#define REACTORCPP_FUELROD_H


#include <Godot.hpp>
#include "../NeutronRegion.h"
#include "../../NeutronField/NeutronField.h"
#include "../../HeatMap/DiffusingHeatMap.h"

namespace nuclearPhysics
{
	class FuelRod : public NeutronRegion
	{
		GODOT_CLASS(FuelRod, nuclearPhysics::NeutronRegion)
	private:
		NeutronField* neutronField = nullptr;

		godot::NodePath thermalMapPath;
		nuclearPhysics::DiffusingHeatMap* thermalMap = nullptr;

		float timeSinceLastFission = 0.0f;

		void spawnFissionNeutron(Neutron &neutron);
		void spawnSpontaneousNeutron();

	public:
		FuelRod();
		~FuelRod() override;

		bool handleNeutron(nuclearPhysics::Neutron &neutron, const godot::Vector2 &globalPosition) override;

		void _init() override;
		void _enter_tree() override;
		void _ready() override;
		void _draw() override;
		virtual void _physics_process(float delta);

		static void _register_methods();

		static constexpr float SPONTANEUOS_FISION_RATE = 0.5f;
		static constexpr float CROSS_SECTION_THERMAL = 0.1f;
		static constexpr float CROSS_SECTION_RELATIVISTIC = 0.01f;
		inline static const char* GROUP = "fuel_rod";
	};
}


#endif //REACTORCPP_FUELROD_H
