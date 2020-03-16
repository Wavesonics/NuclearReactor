//
// Created by Adam on 3/15/2020.
//

#ifndef CPP_BSPREGION1DNODE_H
#define CPP_BSPREGION1DNODE_H

#include <vector>
#include <Godot.hpp>
#include "../NeutronRegion/NeutronRegion.h"

namespace nuclearPhysics
{
	class BspRegion1dNode
	{
	public:
		const godot::Rect2 area;
		const float divider;
		BspRegion1dNode *leftRegion = nullptr;
		BspRegion1dNode *rightRegion = nullptr;
		std::vector<nuclearPhysics::NeutronRegion *> includedRegions;

		BspRegion1dNode(const float x, const godot::Rect2 &nodeArea);

		~BspRegion1dNode();

		bool isInLeft(const float x) const;

		bool isLeaf() const;
	};
}

#endif //CPP_BSPREGION1DNODE_H
