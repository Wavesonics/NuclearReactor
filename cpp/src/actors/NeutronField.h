//
// Created by Adam on 2/27/2020.
//

#ifndef REACTORCPPTEST_NEUTRONFIELD_H
#define REACTORCPPTEST_NEUTRONFIELD_H

#include <vector>
#include <Godot.hpp>
#include <Node2D.hpp>
#include "Neutron.h"
#include "../math/Area2d.h"
#include "NeutronRegion.h"
#include "../util/ThreadPool.h"


namespace nuclearPhysics
{
	class NeutronField : public godot::Node2D
	{
		GODOT_CLASS(NeutronField, godot::Node2D)
	private:
		nuclearPhysics::ThreadPool *threadPool;
		int numWorkers;

		std::vector<nuclearPhysics::Neutron> neutrons;
		std::vector<int> toRemove;
		std::vector<std::vector<int>*>
			workerScratchSpace;

		const nuclearPhysics::Area2d* reactorCore;
		std::vector<nuclearPhysics::NeutronRegion*> regions;

		std::vector<int>* processNeutronBatch(std::vector<int>* removal, int start, int end, float delta);

	public:
		NeutronField();
		~NeutronField();

		void setCapacity(int capacity);
		void addNeutronRegion(nuclearPhysics::NeutronRegion* region);
		void addNeutron(const nuclearPhysics::Neutron& neutron);
		int numNeutrons() const;

		virtual void _init();
		virtual void _physics_process(float delta);
		static void _register_methods();
	};
}


#endif //REACTORCPPTEST_NEUTRONFIELD_H
