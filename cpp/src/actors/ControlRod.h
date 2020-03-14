//
// Created by Adam on 2/28/2020.
//

#ifndef REACTORCPP_CONTROLROD_H
#define REACTORCPP_CONTROLROD_H


#include <Godot.hpp>
#include "NeutronRegion.h"

namespace nuclearPhysics
{
	class ControlRod : public NeutronRegion
	{
		GODOT_CLASS(ControlRod, nuclearPhysics::NeutronRegion)
	private:
		float fullOutPositionDelta;
		float fullInPosition;
		float currentPositionDelta;
		float initialPercentOut;

		float speed = SPEED;
		float scramSpeed = SPEED_SCRAM;
	public:
		ControlRod();
		~ControlRod() override;

		bool handleNeutron(Neutron &neutron) override;
		float percentOut() const;
		void moveOut(float delta, float speed);
		void moveIn(float delta, float speed);
		void updatePosition();

		virtual void _init();
		virtual void _ready();
		virtual void _draw();

		static void _register_methods();
		static constexpr float CROSS_SECTION = 0.1f;
		static constexpr float SPEED = 10.0f;
		static constexpr float SPEED_SCRAM = 100.0f;
		inline static const char* GROUP = "control_rod";
	};
}

#endif //REACTORCPP_CONTROLROD_H
