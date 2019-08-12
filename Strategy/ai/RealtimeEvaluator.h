#pragma once

#include "Evaluator.h"
#include <vector>

namespace player
{
	namespace ai
	{

		class RealtimeEvaluator : public Evaluator
		{

		public:
			std::vector<std::vector<int>> weightSetForDiscCount;

			int eval(std::vector<std::vector<int>> &board, int player) override;


			RealtimeEvaluator(std::vector<std::vector<int>> &weightSet, std::vector<int> &timingSet);

			static int pieces(std::vector<std::vector<int>> &board, int player);

			static std::vector<std::vector<int>> SQUARE_SCORE;

			static int placement(std::vector<std::vector<int>> &board, int player);

			static int stability(std::vector<std::vector<int>> &board, int player);

			static int mobility(std::vector<std::vector<int>> &board, int player);

			static int frontier(std::vector<std::vector<int>> &board, int player);

			static int cornerGrab(std::vector<std::vector<int>> &board, int player);

		};

	}
}
