#include "StaticEvaluator.h"
#include "../../game/BoardHelper.h"

namespace player
{
	namespace ai
	{
		using BoardHelper = game::BoardHelper;

		int StaticEvaluator::eval(std::vector<std::vector<int>> &board, int player)
		{
			int mob = evalMobility(board,player);
			int sc = evalDiscDiff(board,player);
			return 2 * mob + sc + 1000 * evalCorner(board,player);
		}

		int StaticEvaluator::evalDiscDiff(std::vector<std::vector<int>> &board, int player)
		{
			int oplayer = (player == 1) ? 2 : 1;

			int mySC = BoardHelper::getPlayerStoneCount(board,player);
			int opSC = BoardHelper::getPlayerStoneCount(board,oplayer);

			return 100 * (mySC - opSC) / (mySC + opSC);
		}

		int StaticEvaluator::evalMobility(std::vector<std::vector<int>> &board, int player)
		{
			int oplayer = (player == 1) ? 2 : 1;

			int myMoveCount = BoardHelper::getAllPossibleMoves(board,player).size();
			int opMoveCount = BoardHelper::getAllPossibleMoves(board,oplayer).size();

			return 100 * (myMoveCount - opMoveCount) / (myMoveCount + opMoveCount + 1);
		}

		int StaticEvaluator::evalCorner(std::vector<std::vector<int>> &board, int player)
		{
			int oplayer = (player == 1) ? 2 : 1;

			int myCorners = 0;
			int opCorners = 0;

			if (board[0][0] == player)
			{
				myCorners++;
			}
			if (board[7][0] == player)
			{
				myCorners++;
			}
			if (board[0][7] == player)
			{
				myCorners++;
			}
			if (board[7][7] == player)
			{
				myCorners++;
			}

			if (board[0][0] == oplayer)
			{
				opCorners++;
			}
			if (board[7][0] == oplayer)
			{
				opCorners++;
			}
			if (board[0][7] == oplayer)
			{
				opCorners++;
			}
			if (board[7][7] == oplayer)
			{
				opCorners++;
			}

			return 100 * (myCorners - opCorners) / (myCorners + opCorners + 1);
		}

		int StaticEvaluator::evalBoardMap(std::vector<std::vector<int>> &board, int player)
		{
			int oplayer = (player == 1) ? 2 : 1;
			std::vector<std::vector<int>> W =
			{
				std::vector<int> {200, -100, 100, 50, 50, 100, -100, 200},
				std::vector<int> {-100, -200, -50, -50, -50, -50, -200, -100},
				std::vector<int> {100, -50, 100, 0, 0, 100, -50, 100},
				std::vector<int> {50, -50, 0, 0, 0, 0, -50, 50},
				std::vector<int> {50, -50, 0, 0, 0, 0, -50, 50},
				std::vector<int> {100, -50, 100, 0, 0, 100, -50, 100},
				std::vector<int> {-100, -200, -50, -50, -50, -50, -200, -100},
				std::vector<int> {200, -100, 100, 50, 50, 100, -100, 200}
			};

			//if corners are taken W for that 1/4 loses effect
			if (board[0][0] != 0)
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j <= 3; j++)
					{
						W[i][j] = 0;
					}
				}
			}

			if (board[0][7] != 0)
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 4; j <= 7; j++)
					{
						W[i][j] = 0;
					}
				}
			}

			if (board[7][0] != 0)
			{
				for (int i = 5; i < 8; i++)
				{
					for (int j = 0; j <= 3; j++)
					{
						W[i][j] = 0;
					}
				}
			}

			if (board[7][7] != 0)
			{
				for (int i = 5; i < 8; i++)
				{
					for (int j = 4; j <= 7; j++)
					{
						W[i][j] = 0;
					}
				}
			}


			int myW = 0;
			int opW = 0;

			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (board[i][j] == player)
					{
						myW += W[i][j];
					}
					if (board[i][j] == oplayer)
					{
						opW += W[i][j];
					}
				}
			}

			return (myW - opW) / (myW + opW + 1);
		}

		int StaticEvaluator::evalParity(std::vector<std::vector<int>> &board)
		{
			int remDiscs = 64 - BoardHelper::getTotalStoneCount(board);
			return remDiscs % 2 == 0 ? -1 : 1;
		}
	}
}
