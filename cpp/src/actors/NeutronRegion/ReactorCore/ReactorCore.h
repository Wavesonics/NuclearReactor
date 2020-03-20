//
// Created by Adam on 2/28/2020.
//

#ifndef REACTORCPP_REACTORCORE_H
#define REACTORCPP_REACTORCORE_H


#include <Godot.hpp>
#include "../NeutronRegion.h"

namespace nuclearPhysics
{
	class ReactorCore : public NeutronRegion
	{
		GODOT_CLASS(ReactorCore, nuclearPhysics::NeutronRegion)
	public:
		ReactorCore();
		~ReactorCore() override;

		void _init() override;
		void _enter_tree() override;
		void _ready() override;
		void _draw() override;
		bool handleNeutron(nuclearPhysics::Neutron &neutron, const godot::Vector2 &globalPosition) override;

		static void _register_methods();
	};
}

#endif //REACTORCPP_REACTORCORE_H
