//
// Created by Adam on 3/15/2020.
//

#include "BspRegion1dNode.h"
#include <iostream>

using namespace std;
using namespace godot;
using namespace nuclearPhysics;

BspRegion1dNode::BspRegion1dNode(const float x, const godot::Rect2 &nodeArea)
		: divider(x), area(nodeArea), includedRegions(vector<NeutronRegion *>())
{

}

BspRegion1dNode::~BspRegion1dNode()
{
	delete leftRegion;
	delete rightRegion;
}

bool BspRegion1dNode::isLeaf() const
{
	return leftRegion == nullptr && rightRegion == nullptr;
}

bool BspRegion1dNode::isInLeft(const float x) const
{
	return x < divider;
}