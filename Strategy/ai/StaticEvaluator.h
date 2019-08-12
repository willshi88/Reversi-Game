#pragma once

#include "Evaluator.h"
#include <vector>

namespace player
{
	namespace ai
	{


		class StaticEvaluator : public Evaluator
		{

		public:
			int eval(std::vector<std::vector<int>> &board, int player) override;

			static int evalDiscDiff(std::vector<std::vector<int>> &board, int player);

			static int evalMobility(std::vector<std::vector<int>> &board, int player);

			static int evalCorner(std::vector<std::vector<int>> &board, int player);

			static int evalBoardMap(std::vector<std::vector<int>> &board, int player);

			static int evalParity(std::vector<std::vector<int>> &board);


		};

	}
}
