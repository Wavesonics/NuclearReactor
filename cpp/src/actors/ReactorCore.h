//
// Created by Adam on 2/28/2020.
//

#ifndef REACTORCPP_REACTORCORE_H
#define REACTORCPP_REACTORCORE_H


#include <Godot.hpp>
#include "NeutronRegion.h"

namespace nuclearPhysics
{
	class ReactorCore : public NeutronRegion
	{
		GODOT_CLASS(ReactorCore, nuclearPhysics::NeutronRegion)
	public:
		ReactorCore();
		~ReactorCore() override;

		virtual void _init();
		virtual void _ready();
		virtual void _draw();
		bool handleNeutron(Neutron& neutron) override;

		static void _register_methods();
	};
}

#endif //REACTORCPP_REACTORCORE_H
