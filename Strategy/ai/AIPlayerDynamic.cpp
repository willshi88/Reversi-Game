#include "AIPlayerDynamic.h"
#include "Evaluator.h"
#include "DynamicEvaluator.h"
#include "Minimax.h"

namespace player
{
	namespace ai
	{
		using GamePlayer = game::GamePlayer;

		AIPlayerDynamic::AIPlayerDynamic(int mark, int depth) : game::GamePlayer(mark)
		{
			searchDepth = depth;
			evaluator = new DynamicEvaluator();
		}

		bool AIPlayerDynamic::isUserPlayer()
		{
			return false;
		}

		std:: string AIPlayerDynamic::playerName()
		{
			return "Dynamic AI (Depth " + std::to_wstring(searchDepth) + ")";
		}

		Point *AIPlayerDynamic::play(std::vector<std::vector<int>> &board)
		{
			return Minimax::solve(board,myMark,searchDepth,evaluator);
		}
	}
}
