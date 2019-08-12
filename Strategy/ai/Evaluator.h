#pragma once

#include <vector>

namespace player
{
	namespace ai
	{
		class Evaluator
		{

		public:
			virtual int eval(std::vector<std::vector<int>> &board, int player) = 0;

		};

	}
}
