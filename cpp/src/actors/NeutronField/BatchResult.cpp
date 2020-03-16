//
// Created by Adam on 3/15/2020.
//

#include "BatchResult.h"

using namespace std;
using namespace nuclearPhysics;

BatchResult::BatchResult() = default;

BatchResult::BatchResult(vector<int> *list) : toRemove(list)
{

}

BatchResult::~BatchResult() = default;