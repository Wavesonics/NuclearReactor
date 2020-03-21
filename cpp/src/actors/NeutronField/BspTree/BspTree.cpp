//
// Created by Adam on 3/20/2020.
//

#include "BspTree.h"
#include "../Neutron.h"

using namespace std;
using namespace nuclearPhysics;
using namespace godot;

void debugTree(const BspTreeNode *node)
{
	if(node->isLeaf())
	{
		Godot::print("Leaf, x: {0} children: {1}", node->area.get_position().x, node->includedRegions.size());
		/*
		for(auto region : node->includedRegions)
		{
			Godot::print("Region: {0}", region);
		}
		*/
	}
	else
	{
		debugTree(node->leftRegion);
		debugTree(node->rightRegion);
	}
}

BspTree::BspTree()
{

}

BspTree::~BspTree()
{
	delete root;
}

void BspTree::initBspTree(const int maxDepth, const Rect2 &area, const vector<NeutronRegion *> &regions, const NeutronRegion *exclude)
{
	const auto &pos = area.get_position();
	float y = pos.y;
	float height = area.size.height;

	float regionStart = pos.x;
	float regionWidth = area.size.width;

	// Root
	root = createBspBranch(y, height, regionStart, regionWidth, 0, maxDepth);

	// Parse all regions into the leaf's they belong to
	for(auto &region : regions)
	{
		if(region != exclude)
		{
			addToNode(region, root);
		}
	}

	debugTree(root);
}

BspTreeNode *
BspTree::createBspBranch(float y, float height, float start, float parentWidth, int depth, int maxDepth)
{
	const float halfWidth = (parentWidth / 2.0f);
	auto *node = new BspTreeNode(start + halfWidth, Rect2(start, y, parentWidth, height));

	if(depth < maxDepth)
	{
		node->leftRegion = createBspBranch(y, height, start, halfWidth, depth + 1, maxDepth);
		node->rightRegion = createBspBranch(y, height, start + halfWidth, halfWidth, depth + 1, maxDepth);
	}

	return node;
}

void BspTree::addToNode(NeutronRegion *region, BspTreeNode *node)
{
	// If this is a leaf, test to see if we belong here
	if(node->isLeaf())
	{
		Vector2 pos = region->area.position + region->get_position();
		Rect2 area = Rect2(pos, region->area.size);

		// If we intersect in anyway, add our region to this leaf
		if(node->area.intersects(area))
		{
			node->includedRegions.push_back(region);
		}
	}
		// If this node is not a leaf, just pass the region on down
		// until we get to a leaf
	else
	{
		if(node->leftRegion != nullptr)
		{
			addToNode(region, node->leftRegion);
		}

		if(node->rightRegion != nullptr)
		{
			addToNode(region, node->rightRegion);
		}
	}
}

const BspTreeNode *BspTree::getRegionsToCheck(const Neutron &neutron) const
{
	return findRegions(neutron.position.x, root);
}

const BspTreeNode *BspTree::findRegions(const float x, const BspTreeNode *node) const
{
	if(node->isLeaf())
	{
		return node;
	}
	else
	{
		if(node->isInLeft(x))
		{
			return findRegions(x, node->leftRegion);
		}
		else
		{
			return findRegions(x, node->rightRegion);
		}
	}
}

nuclearPhysics::BspTreeNode *BspTree::getRoot()
{
	return root;
}
