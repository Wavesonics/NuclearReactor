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

		bool handleNeutron(Neutron &neutron) override;

		virtual void _init();
		virtual void _ready();
		virtual void _draw();

		static void _register_methods();
		static constexpr float CROSS_SECTION = 0.1f;
	};
}

#endif //REACTORCPPTEST_CONTROLROD_H
