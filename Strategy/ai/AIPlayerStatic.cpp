#include "AIPlayerStatic.h"
#include "Evaluator.h"
#include "StaticEvaluator.h"
#include "Minimax.h"

namespace player
{
	namespace ai
	{
		using GamePlayer = game::GamePlayer;

		AIPlayerStatic::AIPlayerStatic(int mark, int depth) : game::GamePlayer(mark)
		{
			searchDepth = depth;
			evaluator = new StaticEvaluator();
		}

		bool AIPlayerStatic::isUserPlayer()
		{
			return false;
		}

		std:: string AIPlayerStatic::playerName()
		{
			return "Static AI (Depth " + std::to_wstring(searchDepth) + ")";
		}

		Point *AIPlayerStatic::play(std::vector<std::vector<int>> &board)
		{
			return Minimax::solve(board,myMark,searchDepth,evaluator);
		}
	}
}
