//
// Created by Adam on 2/27/2020.
//

#include "NeutronField.h"

#include <iostream>
#include <algorithm>

using namespace std;
using namespace nuclearPhysics;
using namespace godot;

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
	setCapacity(100000);
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

int NeutronField::numNeutrons() const
{
	return neutrons.size();
}

void NeutronField::_physics_process(float delta)
{
	const int n = neutrons.size();
	const int batchSize = n / numWorkers;

	vector<future<vector<int> *>> results;
	results.reserve(numWorkers);

	// Split work load into batches for each hardware thread
	for(int ii = 0; ii < numWorkers; ++ii)
	{
		results.emplace_back(
				threadPool->enqueue([this, ii, batchSize, delta, n] {
					int start = ii * batchSize;
					int end;
					if(ii >= (numWorkers - 1))
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
}

vector<int>* NeutronField::processNeutronBatch(vector<int> *removal, int start, int end, float delta)
{
	for(int ii = start; ii < end; ++ii)
	{
		auto neutron = neutrons[ii];
		Vector2 scaledVelocity = neutron.velocity * delta;
		neutrons[ii].position += scaledVelocity;

		if(!reactorCore->contains(neutron.position))
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

NeutronField::~NeutronField() = default;

void NeutronField::_register_methods()
{
	register_method("setCapacity", &NeutronField::setCapacity);
	register_method("numNeutrons", &NeutronField::numNeutrons);
	register_method("addNeutronRegion", &NeutronField::addNeutronRegion);
	register_method("_init", &NeutronField::_init);
	register_method("_physics_process", &NeutronField::_physics_process);
}