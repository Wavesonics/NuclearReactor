//
// Created by Adam on 3/15/2020.
//

#ifndef CPP_BATCHRESULT_H
#define CPP_BATCHRESULT_H

#include <vector>

namespace nuclearPhysics
{
	struct BatchResult
	{
		int escapedNeutrons = 0;
		std::vector<int> *toRemove;

		BatchResult();

		BatchResult(std::vector<int> *list);

		~BatchResult();
	};
}

#endif //CPP_BATCHRESULT_H
