//
// Created by Adam on 2/27/2020.
//

#ifndef REACTORCPP_MODERATOR_H
#define REACTORCPP_MODERATOR_H


#include <Godot.hpp>
#include "../NeutronRegion.h"
#include "../../NeutronField/NeutronField.h"

namespace nuclearPhysics
{
	class Moderator : public NeutronRegion
	{
		GODOT_CLASS(Moderator, nuclearPhysics::NeutronRegion)
	public:
		Moderator();
		~Moderator() override;

		void _init() override;
		void _enter_tree() override;
		void _ready() override;
		void _draw() override;

		bool handleNeutron(nuclearPhysics::Neutron &neutron, const godot::Vector2 &globalPosition) override;

		static void _register_methods();
		static constexpr float CROSS_SECTION_RELATIVISTIC = 0.1f;
		inline static const char* GROUP = "moderator";
	};
}

#endif //REACTORCPP_MODERATOR_H
