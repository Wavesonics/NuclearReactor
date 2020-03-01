//
// Created by Adam on 2/27/2020.
//

#ifndef REACTORCPPTEST_NEUTRONFIELD_H
#define REACTORCPPTEST_NEUTRONFIELD_H

#include <vector>
#include <Godot.hpp>
#include <Node2D.hpp>
#include "Neutron.h"
#include "ReactorCore.h"
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

		int maxPopulation = 100000;

		godot::NodePath reactorCorePath;
		nuclearPhysics::ReactorCore* reactorCore = NULL;

		std::vector<nuclearPhysics::NeutronRegion*> regions;

		std::vector<int>* processNeutronBatch(std::vector<int>* removal, int start, int end, float delta);

		godot::Color neutronThermalColor;
		godot::Color neutronRelativisticColor;
	public:
		NeutronField();
		~NeutronField();

		void setCapacity(int capacity);
		void addNeutronRegion(nuclearPhysics::NeutronRegion* region);
		void addNeutron(const nuclearPhysics::Neutron& neutron);
		void createNeutron(const godot::Vector2 position, const godot::Vector2 velocity);
		int numNeutrons() const;

		virtual void _init();
		virtual void _ready();
		virtual void _physics_process(float delta);
		virtual void _draw();
		static void _register_methods();
	};
}


#endif //REACTORCPPTEST_NEUTRONFIELD_H
