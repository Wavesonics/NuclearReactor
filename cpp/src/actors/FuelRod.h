//
// Created by Adam on 2/28/2020.
//

#ifndef REACTORCPPTEST_FUELROD_H
#define REACTORCPPTEST_FUELROD_H


#include <Godot.hpp>
#include "NeutronRegion.h"
#include "NeutronField.h"

namespace nuclearPhysics
{
	class FuelRod : public NeutronRegion
	{
		GODOT_CLASS(FuelRod, nuclearPhysics::NeutronRegion)
	private:
		NeutronField *neutronField;
		float timeSinceLastFission = 0.0f;

		void spawnFissionNeutron(Neutron &neutron);

		void spawnSpontaneousNeutron();

	public:
		FuelRod();
		~FuelRod() override;

		virtual void _physics_process(float delta);
		bool handleNeutron(Neutron &neutron) override;
		static void _register_methods();

		static constexpr float SPONTANEUOS_FISION_RATE = 0.5f;
		static constexpr float CROSS_SECTION_THERMAL = 0.1f;
		static constexpr float CROSS_SECTION_RELATIVISTIC = 0.01f;
	};
}


#endif //REACTORCPPTEST_FUELROD_H
