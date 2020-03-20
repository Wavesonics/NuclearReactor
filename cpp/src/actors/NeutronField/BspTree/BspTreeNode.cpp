//
// Created by Adam on 3/15/2020.
//

#include "BspTreeNode.h"
#include <iostream>

using namespace std;
using namespace godot;
using namespace nuclearPhysics;

BspTreeNode::BspTreeNode(const float x, const godot::Rect2 &nodeArea)
		: divider(x), area(nodeArea), includedRegions(vector<NeutronRegion *>())
{

}

BspTreeNode::~BspTreeNode()
{
	delete leftRegion;
	delete rightRegion;
}

bool BspTreeNode::isLeaf() const
{
	return leftRegion == nullptr && rightRegion == nullptr;
}

bool BspTreeNode::isInLeft(const float x) const
{
	return x < divider;
}