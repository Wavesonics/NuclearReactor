//
// Created by Adam on 3/15/2020.
//

#ifndef CPP_BSPTREENODE_H
#define CPP_BSPTREENODE_H

#include <vector>
#include <Godot.hpp>
#include "../../NeutronRegion/NeutronRegion.h"

namespace nuclearPhysics
{
	class BspTreeNode
	{
	public:
		const godot::Rect2 area;
		const float divider;
		BspTreeNode *leftRegion = nullptr;
		BspTreeNode *rightRegion = nullptr;
		std::vector<nuclearPhysics::NeutronRegion *> includedRegions;

		BspTreeNode(const float x, const godot::Rect2 &nodeArea);

		~BspTreeNode();

		bool isInLeft(const float x) const;

		bool isLeaf() const;
	};
}

#endif //CPP_BSPTREENODE_H
