#pragma once

#include <vector>
#include <iostream>
#include <limits>

namespace player { namespace ai { class Evaluator; } }

namespace player
{
	namespace ai
	{
		class Minimax
		{

		public:
			static int nodesExplored;

			//returns max score move
			static Point *solve(std::vector<std::vector<int>> &board, int player, int depth, Evaluator *e);

		private:
			static int MMAB(std::vector<std::vector<int>> &node, int player, int depth, bool max, int alpha, int beta, Evaluator *e);

		};

	}
}
