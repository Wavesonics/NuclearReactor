//
// Created by Adam on 2/28/2020.
//

#ifndef REACTORCPPTEST_CONTROLROD_H
#define REACTORCPPTEST_CONTROLROD_H


#include <Godot.hpp>
#include "NeutronRegion.h"

namespace nuclearPhysics
{
	class ControlRod : public NeutronRegion
	{
		GODOT_CLASS(ControlRod, nuclearPhysics::NeutronRegion)
	public:
		ControlRod();
		~ControlRod() override;

		virtual void _physics_process(float delta);
		bool handleNeutron(Neutron &neutron) override;

		static void _register_methods();
		static constexpr float CROSS_SECTION = 0.1f;
	};
}

#endif //REACTORCPPTEST_CONTROLROD_H
