//
// Created by Adam on 2/28/2020.
//

#ifndef REACTORCPPTEST_REACTORCORE_H
#define REACTORCPPTEST_REACTORCORE_H


#include <Godot.hpp>
#include "NeutronRegion.h"

namespace nuclearPhysics
{
	class ReactorCore : public NeutronRegion
	{
		GODOT_CLASS(ReactorCore, nuclearPhysics::NeutronRegion)
	private:
		godot::Rect2 coreBounds;
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

#endif //REACTORCPPTEST_REACTORCORE_H