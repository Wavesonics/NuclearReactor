//
// Created by Adam on 2/27/2020.
//

#ifndef REACTORCPP_NEUTRONFIELD_H
#define REACTORCPP_NEUTRONFIELD_H

#include <vector>
#include <Godot.hpp>
#include <Node2D.hpp>
#include "Neutron.h"
#include "ReactorCore.h"
#include "NeutronRegion.h"
#include "HeatMap.h"
#include "../util/ThreadPool.h"


namespace nuclearPhysics
{
	struct BatchResult
	{
		int escapedNeutrons = 0;
		std::vector<int>* toRemove;

		BatchResult();
		BatchResult(std::vector<int>* list);
		~BatchResult();
	};

	class NeutronField : public godot::Node2D
	{
		GODOT_CLASS(NeutronField, godot::Node2D)
	private:
		nuclearPhysics::ThreadPool *threadPool;
		int numWorkers;

		std::vector<nuclearPhysics::Neutron> neutrons;
		std::vector<int> toRemove;
		std::vector<std::vector<int>*> workerScratchSpace;

		int maxPopulation = 150000;
		bool enableRendering = true;
		int maxRender = DEFAULT_MAX_RENDER;

		godot::NodePath reactorCorePath;
		nuclearPhysics::ReactorCore* reactorCore = NULL;

		float biproduct = DEFAULT_BIPRODUCT;
		float biproductDecayRate = DEFAULT_BIPRODUCT_DECAY_RATE;
		float biproductFissionRate = DEFAULT_BIPRODUCT_FISSION_RATE;
		godot::NodePath biproductMapPath;
		nuclearPhysics::HeatMap* biproductMap = NULL;

		int neutronFlux = 0;

		void processFissionBiproducts();
		bool processFissionBiproductBatch(float* row, int yy);

		std::vector<nuclearPhysics::NeutronRegion*> regions;

		BatchResult processNeutronBatch(std::vector<int>* removal, int start, int end, float delta);

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
		int getNeutronFlux() const;
		void addFissionBiproduct(const godot::Vector2 &globalPos);
		virtual void _init();
		virtual void _ready();
		virtual void _physics_process(float delta);
		virtual void _draw();

		static void _register_methods();
		static constexpr int DEFAULT_MAX_RENDER = 1500;
		static constexpr float DEFAULT_BIPRODUCT = 0.01f;
		static constexpr float DEFAULT_BIPRODUCT_FISSION_RATE = 0.01f;
		static constexpr float DEFAULT_BIPRODUCT_DECAY_RATE = 0.0005f;
		inline static const char* GROUP = "neutron_field";
	};
}


#endif //REACTORCPP_NEUTRONFIELD_H
