//
// Created by Adam on 2/27/2020.
//

#include "NeutronField.h"
#include "../../util/Utils.h"
#include <Engine.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>
#include <Variant.hpp>
#include <Texture.hpp>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
using namespace nuclearPhysics;
using namespace godot;


static const Color NEUTRON_THERMAL_COLOR = Color(0.5, 0.5, 0.5);
static const Color NEUTRON_RELATIVISTIC_COLOR = Color(0.8, 0.5, 0.0);

BatchResult::BatchResult() = default;

BatchResult::BatchResult(std::vector<int>* list) : toRemove(list)
{

}

BatchResult::~BatchResult() = default;


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

int NeutronField::getMaxPopulation() const
{
	return maxPopulation;
}

void NeutronField::_init()
{
	neutronThermalColor = NEUTRON_THERMAL_COLOR;
	neutronRelativisticColor = NEUTRON_RELATIVISTIC_COLOR;
	maxRender = DEFAULT_MAX_RENDER;
	biproduct = DEFAULT_BIPRODUCT;
	biproductDecayRate = DEFAULT_BIPRODUCT_DECAY_RATE;

	EDITOR_GUARD_RETURN_HERE

	setCapacity(maxPopulation);
}

void NeutronField::_ready()
{
	add_to_group(GROUP);

	EDITOR_GUARD_RETURN_HERE

	// Get the reactor core
	reactorCore = Object::cast_to<ReactorCore>(get_node(reactorCorePath));
	if (reactorCore == nullptr) Godot::print("FAILED TO GET REACTOR CORE!!");

	// Get the biproduct map
	biproductMap = Object::cast_to<HeatMap>(get_node(biproductMapPath));
	if (biproductMap == nullptr) Godot::print("FAILED TO GET BIPRODUCT MAP!!");

	// Get the thermal map
	thermalMap = Object::cast_to<DiffusingHeatMap>(get_node(thermalMapPath));
	if (thermalMap == nullptr) Godot::print("NeutronField: FAILED TO GET THERMAL MAP!!");

	// Register the NeutronField with the control system
    Node* obj = get_tree()->get_root()->find_node("ControlSystem", true, false);
    if (obj != nullptr)
    {
        obj->call("set_neutron_field", Variant(this));
    }
    else
    {
        Godot::print("Failed to get ControlSystem");
    }
}

void NeutronField::setCapacity(int capacity)
{
	numWorkers = (int)std::thread::hardware_concurrency();

	threadPool = new ThreadPool(std::thread::hardware_concurrency());

	const int removeDivisor = 4;
	// During process, we need to allow for Neutrons to be
	// added above the max without crashing
	const float capacityMargin = 1.01f;

	neutrons.reserve((int)((float)capacity * capacityMargin));
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
	// Adding a neutron past maxPopulation will cause a crash
	if (neutrons.size() < maxPopulation-1)
	{
		neutrons.push_back(neutron);
	}
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

int NeutronField::getNeutronFlux() const
{
	return neutronFlux;
}

void NeutronField::addFissionBiproduct(const Vector2 &globalPos)
{
	const Point2& grid = biproductMap->toGrid(globalPos);
	biproductMap->addHeat(biproduct, grid.x, grid.y);
}

Point2 NeutronField::toHeatGrid(const godot::Vector2 &globalPos) const
{
	return thermalMap->toGrid(globalPos);
}

void NeutronField::addHeat(const Vector2 &globalPos, const float heat)
{
	const Point2 &grid = thermalMap->toGrid(globalPos);
	thermalMap->addHeat(heat, grid.x, grid.y);
}

float NeutronField::readHeat(const godot::Vector2 &globalPos) const
{
	const Point2 &grid = thermalMap->toGrid(globalPos);
	return thermalMap->readMagnitude(grid.x, grid.y);
}

void NeutronField::_physics_process(float delta)
{
	EDITOR_GUARD_RETURN_HERE

	const int n = neutrons.size();
	int batchSize = n / numWorkers;

	vector<future<nuclearPhysics::BatchResult>> results;
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
					// Last worker will take the remainder of jobs left
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

	neutronFlux = 0;

	// Collect results
	for(auto& future : results)
	{
		const auto &result = future.get();
		neutronFlux += result.escapedNeutrons;

		auto removals = result.toRemove;
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

	processFissionBiproducts();
}

BatchResult NeutronField::processNeutronBatch(vector<int> *removal, int start, int end, float delta)
{
	BatchResult result = BatchResult(removal);

	for(int ii = start; ii < end; ++ii)
	{
		auto & neutron = neutrons[ii];
		Vector2 scaledVelocity = neutron.velocity * delta;
		neutron.position += scaledVelocity;

		const Vector2 &globalPos = to_global(neutron.position);
		if(!reactorCore->contains(globalPos))
		{
			result.escapedNeutrons++;
			removal->push_back(ii);
		}
		else
		{
			for(auto region : regions)
			{
				if(region->contains(globalPos))
				{
					if(region->handleNeutron(neutron, globalPos))
					{
						removal->push_back(ii);
						break; // No need to continue, we've been removed
					}
				}
			}
		}
	}

	return result;
}

void NeutronField::processFissionBiproducts()
{
	vector<future<bool>> results;

	auto map = biproductMap->map;
	int mapSize = biproductMap->mapSize;

	// Assign each row to it's own worker
	for (int yy = 0; yy < mapSize; ++yy)
	{
		float* row = map[yy];
		results.emplace_back(
			threadPool->enqueue([this, row, yy] {
				return processFissionBiproductBatch(row, yy);
				})
		);
	}

	// Wait for all workers to finish
	for (auto& result : results)
	{
		const auto& done = result.get();
	}

	biproductMap->update();
}

// Process an individual row of the Biproduct heatmap
bool NeutronField::processFissionBiproductBatch(float *row, int yy)
{
	int mapSize = biproductMap->mapSize;
	for (int xx = 0; xx < mapSize; ++xx)
	{
		const float biproductDensity = row[xx];

		// Biproducts decay over time
		row[xx] = clamp(biproductDensity - biproductDecayRate, 0.0f, 1.0f);

		// Random change of biproducts fissioning and releasing a Neutron
		if ((biproductFissionRate*biproductDensity) > randf(0.0000001, 1.0))
		{
			auto pos = reactorCore->get_global_position() + reactorCore->area.position;
			pos.x += biproductMap->cellWidth * (float)xx;
			pos.y += biproductMap->cellHeight * (float)yy;

			auto vel = rand_vec2(-1.0f, 1.0f) * Neutron::SPEED_RELATIVISTIC;

			auto neutron = Neutron(pos, vel);
			addNeutron(neutron);
		}
	}

	return true;
}

void NeutronField::_draw()
{
	if (enableRendering && !neutrons.empty())
	{
		const int num = neutrons.size();
		const int step = max(1, num / maxRender);

		int rendered = 0;

		auto neutronThermalColorArray = PoolColorArray(Array::make(neutronThermalColor));
		auto neutronRelativisticColorArray = PoolColorArray(Array::make(neutronRelativisticColor));
		auto emptyArray = PoolVector2Array();
		auto point = PoolVector2Array(Array::make(Vector2()));

		for(int ii=0; ii< num; ii += step)
		{
			const Neutron &n = neutrons[ii];
			point.set(0, n.position);

			if (n.isThermalized())
			{
				draw_primitive(point, neutronThermalColorArray, emptyArray);
			}
			else
			{
				draw_primitive(point, neutronRelativisticColorArray, emptyArray);
			}

			// Don't allow us to render more tha maxRender
			++rendered;
			if (rendered >= maxRender)
			{
				break;
			}
		}
	}
}

NeutronField::~NeutronField() = default;

void NeutronField::_register_methods()
{
	register_property<NeutronField, NodePath>("reactorCorePath", &NeutronField::reactorCorePath, nullptr);
	register_property<NeutronField, NodePath>("biproductMapPath", &NeutronField::biproductMapPath, nullptr);
	register_property<NeutronField, NodePath>("thermalMapPath", &NeutronField::thermalMapPath, nullptr);
	register_property<NeutronField, float>("biproduct", &NeutronField::biproduct, NeutronField::DEFAULT_BIPRODUCT);
	register_property<NeutronField, float>("biproductFissionRate", &NeutronField::biproductFissionRate, NeutronField::DEFAULT_BIPRODUCT_FISSION_RATE);
	register_property<NeutronField, float>("biproductDecayRate", &NeutronField::biproductDecayRate, NeutronField::DEFAULT_BIPRODUCT_DECAY_RATE);
	register_property<NeutronField, bool>("enableRendering", &NeutronField::enableRendering, true);
	register_property<NeutronField, int>("maxRender", &NeutronField::maxRender, NeutronField::DEFAULT_MAX_RENDER);
	//register_property<NeutronField, int>("maxPopulation", &NeutronField::maxPopulation, 100000);

	register_method("get_max_population", &NeutronField::getMaxPopulation);
	//register_method("set_capacity", &NeutronField::setCapacity);
	register_method("num_neutrons", &NeutronField::numNeutrons);
	register_method("create_neutron", &NeutronField::createNeutron);
	register_method("add_neutron_region", &NeutronField::addNeutronRegion);
	register_method("add_fission_biproduct", &NeutronField::addFissionBiproduct);
	register_method("add_heat", &NeutronField::addHeat);
	register_method("read_heat", &NeutronField::readHeat);
	register_method("to_heat_grid", &NeutronField::toHeatGrid);
	register_method("get_neutron_flux", &NeutronField::getNeutronFlux);
	
	register_method("_init", &NeutronField::_init);
	register_method("_ready", &NeutronField::_ready);
	register_method("_physics_process", &NeutronField::_physics_process);
	register_method("_draw", &NeutronField::_draw);
}