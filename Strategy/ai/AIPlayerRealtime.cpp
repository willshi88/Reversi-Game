#include "AIPlayerRealtime.h"
#include "Evaluator.h"
#include "RealtimeEvaluator.h"
#include "Minimax.h"

namespace player
{
	namespace ai
	{
		using GamePlayer = game::GamePlayer;

		AIPlayerRealtime::AIPlayerRealtime(int mark, int depth) : game::GamePlayer(mark)
		{
			searchDepth = depth;

			if (mark == 1)
			{
				evaluator = new RealtimeEvaluator(std::vector<std::vector<int>>
				{
					std::vector<int> {8, 85, -40, 10, 210, 520},
					std::vector<int> {8, 85, -40, 10, 210, 520},
					std::vector<int> {33, -50, -15, 4, 416, 2153},
					std::vector<int> {46, -50, -1, 3, 612, 4141},
					std::vector<int> {51, -50, 62, 3, 595, 3184},
					std::vector<int> {33, -5, 66, 2, 384, 2777},
					std::vector<int> {44, 50, 163, 0, 443, 2568},
					std::vector<int> {13, 50, 66, 0, 121, 986},
					std::vector<int> {4, 50, 31, 0, 27, 192},
					std::vector<int> {8, 500, 77, 0, 36, 299}
				}, std::vector<int> {0, 55, 56, 57, 58, 59, 60, 61, 62, 63});
			}
			else
			{
				evaluator = new RealtimeEvaluator(std::vector<std::vector<int>>
				{
					std::vector<int> {8, 85, -40, 10, 210, 520},
					std::vector<int> {8, 85, -40, 10, 210, 520},
					std::vector<int> {33, -50, -15, 4, 416, 2153},
					std::vector<int> {46, -50, -1, 3, 612, 4141},
					std::vector<int> {51, -50, 62, 3, 595, 3184},
					std::vector<int> {33, -5, 66, 2, 384, 2777},
					std::vector<int> {44, 50, 163, 0, 443, 2568},
					std::vector<int> {13, 50, 66, 0, 121, 986},
					std::vector<int> {4, 50, 31, 0, 27, 192},
					std::vector<int> {8, 500, 77, 0, 36, 299}
				}, std::vector<int> {0, 55, 56, 57, 58, 59, 60, 61, 62, 63});
			}
		}

		bool AIPlayerRealtime::isUserPlayer()
		{
			return false;
		}

		std:: string AIPlayerRealtime::playerName()
		{
			return "Realtime AI (Depth " + std::to_wstring(searchDepth) + ")";
		}

		Point *AIPlayerRealtime::play(std::vector<std::vector<int>> &board)
		{
			return Minimax::solve(board,myMark,searchDepth,evaluator);
		}
	}
}
