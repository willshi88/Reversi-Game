#include "DynamicEvaluator.h"
#include "../../game/BoardHelper.h"
#include "StaticEvaluator.h"

namespace player
{
	namespace ai
	{
		using BoardHelper = game::BoardHelper;
		using namespace player::ai;

		DynamicEvaluator::GamePhase DynamicEvaluator::getGamePhase(std::vector<std::vector<int>> &board)
		{
			int sc = BoardHelper::getTotalStoneCount(board);
			if (sc < 20)
			{
				return GamePhase::EARLY_GAME;
			}
			else if (sc <= 58)
			{
				return GamePhase::MID_GAME;
			}
			else
			{
				return GamePhase::LATE_GAME;
			}
		}

		int DynamicEvaluator::eval(std::vector<std::vector<int>> &board, int player)
		{

			//terminal
			if (BoardHelper::isGameFinished(board))
			{
				return 1000 * StaticEvaluator::evalDiscDiff(board, player);
			}

			//semi-terminal
			switch (getGamePhase(board))
			{
				case EARLY_GAME:
					return 1000 * StaticEvaluator::evalCorner(board,player) + 50 * StaticEvaluator::evalMobility(board,player);
				case MID_GAME:
					return 1000 * StaticEvaluator::evalCorner(board,player) + 20 * StaticEvaluator::evalMobility(board,player) + 10 * StaticEvaluator::evalDiscDiff(board, player) + 100 * StaticEvaluator::evalParity(board);
				case LATE_GAME:
				default:
					return 1000 * StaticEvaluator::evalCorner(board,player) + 100 * StaticEvaluator::evalMobility(board,player) + 500 * StaticEvaluator::evalDiscDiff(board, player) + 500 * StaticEvaluator::evalParity(board);
			}
		}
	}
}
