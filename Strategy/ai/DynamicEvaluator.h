#pragma once

#include "Evaluator.h"
#include <vector>

namespace player
{
	namespace ai
	{

		using namespace player::ai;

		class DynamicEvaluator : public Evaluator
		{

			//Evaluation Function Changes during Early-Game / Mid-Game / Late-Game
		public:
			enum class GamePhase
			{
				EARLY_GAME,
				MID_GAME,
				LATE_GAME
			};

		private:
			GamePhase getGamePhase(std::vector<std::vector<int>> &board);

		public:
			int eval(std::vector<std::vector<int>> &board, int player) override;

		};

	}
}
