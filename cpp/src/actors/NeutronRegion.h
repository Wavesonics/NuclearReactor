//
// Created by Adam on 2/27/2020.
//

#ifndef REACTORCPPTEST_NEUTRONREGION_H
#define REACTORCPPTEST_NEUTRONREGION_H

#include <Godot.hpp>
#include <Node2D.hpp>
#include "Neutron.h"


namespace nuclearPhysics
{
	class NeutronRegion : public godot::Node2D
	{
		GODOT_CLASS(NeutronRegion, godot::Node2D)
	protected:
		godot::Rect2 globalArea;
		godot::Color drawColor;
	public:
		godot::Rect2 area;

		NeutronRegion();
		virtual ~NeutronRegion();

		/**
		 * Peform what ever logic and processing this region does on Neutrons that
		 * are contained inside of it.
		 * @param neutron
		 * @return true if the Neutron should be removed from the simulation
		 */
		virtual bool handleNeutron(nuclearPhysics::Neutron &neutron) = 0;

		// Convenience method for checking the area
		bool contains(const godot::Point2 &point) const;

		virtual void _init();
		virtual void _ready();
		virtual void _draw();

		static void _register_methods();
	};
}

#endif //REACTORCPPTEST_NEUTRONREGION_H
