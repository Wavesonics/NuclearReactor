//
// Created by Adam on 2/27/2020.
//

#include "NeutronField.h"
#include "../util/Utils.h"
#include <iostream>
#include <algorithm>

using namespace std;
using namespace nuclearPhysics;
using namespace godot;


//const string NeutronField::GROUP = "neutron_field";

template<class Container, class Iterator>
Iterator reorderingErase(Container &c, Iterator it)
{
	if(&(*it) == &(c.back()))
	{
		c.pop_back();
		return std::end(c);
	}
	else
	{
		*it = std::move(c.back());
		c.pop_back();
		return it;
	}
}

NeutronField::NeutronField() : Node2D()
{
	
}

void NeutronField::_init()
{
	setCapacity(maxPopulation);

	neutronThermalColor = godot::Color();
	neutronThermalColor.a = 1.0f;
	neutronThermalColor.r = 0.5f;
	neutronThermalColor.g = 0.5f;
	neutronThermalColor.b = 0.5f;

	neutronRelativisticColor = godot::Color();
	neutronRelativisticColor.a = 1.0f;
	neutronRelativisticColor.r = 0.8f;
	neutronRelativisticColor.g = 0.5f;
	neutronRelativisticColor.b = 0.0f;
}

void NeutronField::_ready()
{
	ReactorCore* obj = Object::cast_to<ReactorCore>(get_node(reactorCorePath));
	if (obj != nullptr)
	{
		reactorCore = obj;
	}
	else
	{
		Godot::print("FAILED TO GET REACTOR CORE!!");
	}

	//add_to_group(NeutronField::GROUP);
	add_to_group("neutron_field");
}

void NeutronField::setCapacity(int capacity)
{
	numWorkers = (int)std::thread::hardware_concurrency();

	threadPool = new ThreadPool(std::thread::hardware_concurrency());

	const int removeDivisor = 4;

	neutrons.reserve(capacity);
	toRemove.reserve(capacity / removeDivisor);

	for (int ii = 0; ii < numWorkers; ++ii)
	{
		auto space = new vector<int>();
		space->reserve((capacity / removeDivisor) / numWorkers);
		workerScratchSpace.push_back(space);
	}
}

void NeutronField::addNeutronRegion(NeutronRegion *region)
{
	regions.push_back(region);
}

void NeutronField::addNeutron(const Neutron &neutron)
{
	neutrons.push_back(neutron);
}

void NeutronField::createNeutron(const godot::Vector2 position, const godot::Vector2 velocity)
{
	auto neutron = Neutron(position, velocity);
	addNeutron(neutron);
}

int NeutronField::numNeutrons() const
{
	return neutrons.size();
}

void NeutronField::_physics_process(float delta)
{
	const int n = neutrons.size();
	int batchSize = n / numWorkers;

	vector<future<vector<int>*>> results;
	if (n >= numWorkers)
	{
		results.reserve(numWorkers);

		// Split work load into batches for each hardware thread
		for (int ii = 0; ii < numWorkers; ++ii)
		{
			results.emplace_back(
				threadPool->enqueue([this, ii, batchSize, delta, n] {
					int start = ii * batchSize;
					int end;
					if (ii >= (numWorkers - 1))
					{
						end = n - 1;
					}
					else
					{
						end = start + batchSize;
					}
					auto& removal = workerScratchSpace[ii];

					return processNeutronBatch(removal, start, end, delta);
					})
			);
		}
	}	
	// Not enough neutrons, just use 1 thread
	else
	{
		results.emplace_back(
			threadPool->enqueue([this, delta, n] {
				auto& removal = workerScratchSpace[0];
				return processNeutronBatch(removal, 0, n, delta);
				})
		);
	}

	// Collect results
	for(auto& result : results)
	{
		const auto &removals = result.get();
		copy(removals->begin(), removals->end(), back_inserter(toRemove));
		removals->clear();
	}

	// Sort in ascending order
	sort(toRemove.begin(), toRemove.end());
	// Iterate in reverse order
	for(auto index = toRemove.crbegin(); index != toRemove.crend(); ++index)
	{
		reorderingErase(neutrons, neutrons.begin() + *index);
	}
	toRemove.clear();

	update();
}

vector<int>* NeutronField::processNeutronBatch(vector<int> *removal, int start, int end, float delta)
{
	for(int ii = start; ii < end; ++ii)
	{
		auto & neutron = neutrons[ii];
		Vector2 scaledVelocity = neutron.velocity * delta;
		neutron.position += scaledVelocity;

		//cout << neutron.velocity.x << ", " << neutron.velocity.y << endl;

		if(reactorCore != NULL && !reactorCore->contains(neutron.position))
		{
			removal->push_back(ii);
		}
		else
		{
			for(auto region : regions)
			{
				if(region->contains(neutron.position))
				{
					if(region->handleNeutron(neutron))
					{
						removal->push_back(ii);
					}
				}
			}
		}
	}

	return removal;
}

void NeutronField::_draw()
{
	if (enableRendering)
	{
		for (auto& n : neutrons)
		{
			if (n.isThermalized())
			{
				draw_circle(n.position, 1.0f, neutronThermalColor);
			}
			else
			{
				draw_circle(n.position, 1.0f, neutronRelativisticColor);
			}
		}
	}
}

NeutronField::~NeutronField() = default;

void NeutronField::_register_methods()
{
	register_property<NeutronField, NodePath>("reactorCorePath", &NeutronField::reactorCorePath, NULL);
	register_property<NeutronField, bool>("enableRendering", &NeutronField::enableRendering, true);
	//register_property<NeutronField, int>("maxPopulation", &NeutronField::maxPopulation, 100000);

	register_method("setCapacity", &NeutronField::setCapacity);
	register_method("numNeutrons", &NeutronField::numNeutrons);
	register_method("createNeutron", &NeutronField::createNeutron);
	register_method("addNeutronRegion", &NeutronField::addNeutronRegion);
	register_method("_init", &NeutronField::_init);
	register_method("_ready", &NeutronField::_ready);
	register_method("_physics_process", &NeutronField::_physics_process);
	register_method("_draw", &NeutronField::_draw);
}