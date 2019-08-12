#include "RealtimeEvaluator.h"
#include "../../game/BoardHelper.h"

namespace player
{
	namespace ai
	{
		using BoardHelper = game::BoardHelper;

		int RealtimeEvaluator::eval(std::vector<std::vector<int>> &board, int player)
		{
			int score = 0;

			std::vector<int> weights = weightSetForDiscCount[BoardHelper::getTotalStoneCount(board)];

			if (weights[0] != 0)
			{
				score += weights[0] * mobility(board,player);
			}
			if (weights[1] != 0)
			{
				score += weights[1] * frontier(board,player);
			}
			if (weights[2] != 0)
			{
				score += weights[2] * pieces(board,player);
			}
			if (weights[3] != 0)
			{
				score += weights[3] * placement(board,player);
			}
			if (weights[4] != 0)
			{
				score += weights[4] * stability(board,player);
			}
			if (weights[5] != 0)
			{
				score += weights[5] * cornerGrab(board,player);
			}

			return score;
		}

		RealtimeEvaluator::RealtimeEvaluator(std::vector<std::vector<int>> &weightSet, std::vector<int> &timingSet)
		{

            vector<vector<int>> weightSetForDiscCount (8, vector<int> (8, 0));
			weightSetForDiscCount = RectangularVectors::RectangularIntVector(65, weightSet[0].size());

			//dc : Disk Count
			for (int dc = 0; dc <= 64; dc++)
			{
				// determine which set of weights to use
				int w = 0;
				for (int i = 0; i < timingSet.size(); i++)
				{
					if (dc <= timingSet[i])
					{
						w = i;
						break;
					}
				}

				// first set of weights: just return them
				if (w == 0)
				{
					weightSetForDiscCount[dc] = weightSet[0];
					continue;
				}

				// linearly interpolate between the set of weights given for the
				// current number of moves and the previous set of weights
				double factor = (static_cast<double>(dc) - timingSet[w - 1]) / (timingSet[w] - timingSet[w - 1]);
				for (int i = 0; i < weightSet[w].size(); i++)
				{
					weightSetForDiscCount[dc][i] = static_cast<int>(BankersRounding::round(factor * weightSet[w][i] + (1 - factor) * weightSet[w - 1][i]));
				}
			}
		}

		int RealtimeEvaluator::pieces(std::vector<std::vector<int>> &board, int player)
		{
			int oplayer = (player == 1) ? 2 : 1;

			int mySC = BoardHelper::getPlayerStoneCount(board,player);
			int opSC = BoardHelper::getPlayerStoneCount(board,oplayer);

			return 100 * (mySC - opSC) / (mySC + opSC + 1);
		}

std::vector<std::vector<int>> RealtimeEvaluator::SQUARE_SCORE =
{
	{100, -10, 8, 6, 6, 8, -10, 100},
	{-10, -25, -4, -4, -4, -4, -25, -10},
	{8, -4, 6, 4, 4, 6, -4, 8},
	{6, -4, 4, 0, 0, 4, -4, 6},
	{6, -4, 4, 0, 0, 4, -4, 6},
	{8, -4, 6, 4, 4, 6, -4, 8},
	{-10, -25, -4, -4, -4, -4, -25, -10},
	{100, -10, 8, 6, 6, 8, -10, 100}
};

		int RealtimeEvaluator::placement(std::vector<std::vector<int>> &board, int player)
		{
			int oplayer = (player == 1) ? 2 : 1;

			int myW = 0;
			int opW = 0;

			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (board[i][j] == player)
					{
						myW += SQUARE_SCORE[i][j];
					}
					if (board[i][j] == oplayer)
					{
						opW += SQUARE_SCORE[i][j];
					}
				}
			}

			return myW - opW;
		}

		int RealtimeEvaluator::stability(std::vector<std::vector<int>> &board, int player)
		{
			int oplayer = (player == 1) ? 2 : 1;

			int myS = 0;
			int opS = 0;

			if (board[0][0] == player)
			{
				myS += BoardHelper::getStableDisks(board,player,0,0).size();
			}
			if (board[0][7] == player)
			{
				myS += BoardHelper::getStableDisks(board,player,0,7).size();
			}
			if (board[7][0] == player)
			{
				myS += BoardHelper::getStableDisks(board,player,7,0).size();
			}
			if (board[7][7] == player)
			{
				myS += BoardHelper::getStableDisks(board,player,7,7).size();
			}

			if (board[0][0] == oplayer)
			{
				opS += BoardHelper::getStableDisks(board,oplayer,0,0).size();
			}
			if (board[0][7] == oplayer)
			{
				opS += BoardHelper::getStableDisks(board,oplayer,0,7).size();
			}
			if (board[7][0] == oplayer)
			{
				opS += BoardHelper::getStableDisks(board,oplayer,7,0).size();
			}
			if (board[7][7] == oplayer)
			{
				opS += BoardHelper::getStableDisks(board,oplayer,7,7).size();
			}

			return 100 * (myS - opS) / (myS + opS + 1);
		}

		int RealtimeEvaluator::mobility(std::vector<std::vector<int>> &board, int player)
		{
			int oplayer = (player == 1) ? 2 : 1;

			int myMoveCount = BoardHelper::getAllPossibleMoves(board,player).size();
			int opMoveCount = BoardHelper::getAllPossibleMoves(board,oplayer).size();

			return 100 * (myMoveCount - opMoveCount) / (myMoveCount + opMoveCount + 1);
		}

		int RealtimeEvaluator::frontier(std::vector<std::vector<int>> &board, int player)
		{
			int oplayer = (player == 1) ? 2 : 1;

			int myF = BoardHelper::getFrontierSquares(board,player).size();
			int opF = BoardHelper::getFrontierSquares(board,oplayer).size();

			return 100 * (myF - opF) / (myF + opF + 1);
		}

		int RealtimeEvaluator::cornerGrab(std::vector<std::vector<int>> &board, int player)
		{
			std::vector<Point*> moves = BoardHelper::getAllPossibleMoves(board,player);

			for (auto m : moves)
			{
				//if player have corner move return 1
				if (m->x == 0 && m->y == 0)
				{
					return 100;
				}
				if (m->x == 7 && m->y == 0)
				{
					return 100;
				}
				if (m->x == 0 && m->y == 7)
				{
					return 100;
				}
				if (m->x == 7 && m->y == 7)
				{
					return 100;
				}
			}

			return 0;
		}
	}
}
