//
// Created by Adam on 3/20/2020.
//

#ifndef CPP_BSPTREE_H
#define CPP_BSPTREE_H

#include <Godot.hpp>
#include "BspTreeNode.h"

namespace nuclearPhysics
{
	class BspTree
	{
	private:
		nuclearPhysics::BspTreeNode *root = nullptr;
	public:
		BspTree();
		~BspTree();

		void initBspTree(const int maxDepth, const godot::Rect2 &area, const std::vector<nuclearPhysics::NeutronRegion *> &regions,
						 const nuclearPhysics::NeutronRegion *exclude);

		BspTreeNode *createBspBranch(float y, float height, float start, float width, int depth, int maxDepth);

		const nuclearPhysics::BspTreeNode *getRegionsToCheck(const Neutron &neutron) const;

		const nuclearPhysics::BspTreeNode *findRegions(const float x, const BspTreeNode *node) const;

		void addToNode(NeutronRegion *region, BspTreeNode *node);

		nuclearPhysics::BspTreeNode *getRoot();
	};
}

#endif //CPP_BSPTREE_H
