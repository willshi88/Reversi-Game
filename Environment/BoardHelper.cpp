#include "BoardHelper.h"

namespace game
{

	bool BoardHelper::isGameFinished(std::vector<std::vector<int>> &board)
	{
	   return !(hasAnyMoves(board,1) || hasAnyMoves(board,2));
	}

	std::vector<std::vector<int>> BoardHelper::getStartBoard()
	{

        vector<vector<int>> b (8, vector<int> (8, 0));
		std::vector<std::vector<int>> b = RectangularVectors::RectangularIntVector(8, 8);
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				b[i][j] = 0;
			}
		}
		b[3][3] = 2;
		b[3][4] = 1;
		b[4][3] = 1;
		b[4][4] = 2;
		return b;
	}

	Point *BoardHelper::getMove(std::vector<std::vector<int>> &before, std::vector<std::vector<int>> &after)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (before[i][j] == 0 && after[i][j] != 0)
				{
					return new Point(i,j);
				}
			}
		}
		return nullptr;
	}

	int BoardHelper::getWinner(std::vector<std::vector<int>> &board)
	{
		if (!isGameFinished(board))
		{
			//game not finished
			return -1;
		}
		else
		{
			//count stones
			int p1s = getPlayerStoneCount(board,1);
			int p2s = getPlayerStoneCount(board,2);

			if (p1s == p2s)
			{
				//tie
				return 0;
			}
			else if (p1s > p2s)
			{
				//p1 wins
				return 1;
			}
			else
			{
				//p2 wins
				return 2;
			}
		}
	}

	int BoardHelper::getTotalStoneCount(std::vector<std::vector<int>> &board)
	{
		int c = 0;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] != 0)
				{
					c++;
				}
			}
		}
		return c;
	}

	int BoardHelper::getPlayerStoneCount(std::vector<std::vector<int>> &board, int player)
	{
		int score = 0;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] == player)
				{
					score++;
				}
			}
		}
		return score;
	}

	bool BoardHelper::hasAnyMoves(std::vector<std::vector<int>> &board, int player)
	{
		return getAllPossibleMoves(board,player).size() > 0;
	}

	std::vector<Point*> BoardHelper::getAllPossibleMoves(std::vector<std::vector<int>> &board, int player)
	{
		std::vector<Point*> result;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (canPlay(board,player,i,j))
				{
					Point tempVar(i,j);
					result.push_back(&tempVar);
				}
			}
		}
		return result;
	}

	std::vector<Point*> BoardHelper::getReversePoints(std::vector<std::vector<int>> &board, int player, int i, int j)
	{

		std::vector<Point*> allReversePoints;

		int mi, mj, c;
		int oplayer = ((player == 1) ? 2 : 1);

		//move up
		std::vector<Point*> mupts;
		mi = i - 1;
		mj = j;
		while (mi > 0 && board[mi][mj] == oplayer)
		{
			Point tempVar(mi,mj);
			mupts.push_back(&tempVar);
			mi--;
		}
		if (mi >= 0 && board[mi][mj] == player && mupts.size() > 0)
		{
			allReversePoints.insert(allReversePoints.end(), mupts.begin(), mupts.end());
		}


		//move down
		std::vector<Point*> mdpts;
		mi = i + 1;
		mj = j;
		while (mi < 7 && board[mi][mj] == oplayer)
		{
			Point tempVar2(mi,mj);
			mdpts.push_back(&tempVar2);
			mi++;
		}
		if (mi <= 7 && board[mi][mj] == player && mdpts.size() > 0)
		{
			allReversePoints.insert(allReversePoints.end(), mdpts.begin(), mdpts.end());
		}

		//move left
		std::vector<Point*> mlpts;
		mi = i;
		mj = j - 1;
		while (mj > 0 && board[mi][mj] == oplayer)
		{
			Point tempVar3(mi,mj);
			mlpts.push_back(&tempVar3);
			mj--;
		}
		if (mj >= 0 && board[mi][mj] == player && mlpts.size() > 0)
		{
			allReversePoints.insert(allReversePoints.end(), mlpts.begin(), mlpts.end());
		}

		//move right
		std::vector<Point*> mrpts;
		mi = i;
		mj = j + 1;
		while (mj < 7 && board[mi][mj] == oplayer)
		{
			Point tempVar4(mi,mj);
			mrpts.push_back(&tempVar4);
			mj++;
		}
		if (mj <= 7 && board[mi][mj] == player && mrpts.size() > 0)
		{
			allReversePoints.insert(allReversePoints.end(), mrpts.begin(), mrpts.end());
		}

		//move up left
		std::vector<Point*> mulpts;
		mi = i - 1;
		mj = j - 1;
		while (mi > 0 && mj > 0 && board[mi][mj] == oplayer)
		{
			Point tempVar5(mi,mj);
			mulpts.push_back(&tempVar5);
			mi--;
			mj--;
		}
		if (mi >= 0 && mj >= 0 && board[mi][mj] == player && mulpts.size() > 0)
		{
			allReversePoints.insert(allReversePoints.end(), mulpts.begin(), mulpts.end());
		}

		//move up right
		std::vector<Point*> murpts;
		mi = i - 1;
		mj = j + 1;
		while (mi > 0 && mj < 7 && board[mi][mj] == oplayer)
		{
			Point tempVar6(mi,mj);
			murpts.push_back(&tempVar6);
			mi--;
			mj++;
		}
		if (mi >= 0 && mj <= 7 && board[mi][mj] == player && murpts.size() > 0)
		{
			allReversePoints.insert(allReversePoints.end(), murpts.begin(), murpts.end());
		}

		//move down left
		std::vector<Point*> mdlpts;
		mi = i + 1;
		mj = j - 1;
		while (mi < 7 && mj>0 && board[mi][mj] == oplayer)
		{
			Point tempVar7(mi,mj);
			mdlpts.push_back(&tempVar7);
			mi++;
			mj--;
		}
		if (mi <= 7 && mj >= 0 && board[mi][mj] == player && mdlpts.size() > 0)
		{
			allReversePoints.insert(allReversePoints.end(), mdlpts.begin(), mdlpts.end());
		}

		//move down right
		std::vector<Point*> mdrpts;
		mi = i + 1;
		mj = j + 1;
		while (mi < 7 && mj < 7 && board[mi][mj] == oplayer)
		{
			Point tempVar8(mi,mj);
			mdrpts.push_back(&tempVar8);
			mi++;
			mj++;
		}
		if (mi <= 7 && mj <= 7 && board[mi][mj] == player && mdrpts.size() > 0)
		{
			allReversePoints.insert(allReversePoints.end(), mdrpts.begin(), mdrpts.end());
		}

		return allReversePoints;
	}

	bool BoardHelper::canPlay(std::vector<std::vector<int>> &board, int player, int i, int j)
	{

		if (board[i][j] != 0)
		{
			return false;
		}

		int mi, mj, c;
		int oplayer = ((player == 1) ? 2 : 1);

		//move up
		mi = i - 1;
		mj = j;
		c = 0;
		while (mi > 0 && board[mi][mj] == oplayer)
		{
			mi--;
			c++;
		}
		if (mi >= 0 && board[mi][mj] == player && c > 0)
		{
			return true;
		}


		//move down
		mi = i + 1;
		mj = j;
		c = 0;
		while (mi < 7 && board[mi][mj] == oplayer)
		{
			mi++;
			c++;
		}
		if (mi <= 7 && board[mi][mj] == player && c>0)
		{
			return true;
		}

		//move left
		mi = i;
		mj = j - 1;
		c = 0;
		while (mj > 0 && board[mi][mj] == oplayer)
		{
			mj--;
			c++;
		}
		if (mj >= 0 && board[mi][mj] == player && c > 0)
		{
			return true;
		}

		//move right
		mi = i;
		mj = j + 1;
		c = 0;
		while (mj < 7 && board[mi][mj] == oplayer)
		{
			mj++;
			c++;
		}
		if (mj <= 7 && board[mi][mj] == player && c>0)
		{
			return true;
		}

		//move up left
		mi = i - 1;
		mj = j - 1;
		c = 0;
		while (mi > 0 && mj > 0 && board[mi][mj] == oplayer)
		{
			mi--;
			mj--;
			c++;
		}
		if (mi >= 0 && mj >= 0 && board[mi][mj] == player && c > 0)
		{
			return true;
		}

		//move up right
		mi = i - 1;
		mj = j + 1;
		c = 0;
		while (mi > 0 && mj < 7 && board[mi][mj] == oplayer)
		{
			mi--;
			mj++;
			c++;
		}
		if (mi >= 0 && mj <= 7 && board[mi][mj] == player && c>0)
		{
			return true;
		}

		//move down left
		mi = i + 1;
		mj = j - 1;
		c = 0;
		while (mi < 7 && mj>0 && board[mi][mj] == oplayer)
		{
			mi++;
			mj--;
			c++;
		}
		if (mi <= 7 && mj >= 0 && board[mi][mj] == player && c > 0)
		{
			return true;
		}

		//move down right
		mi = i + 1;
		mj = j + 1;
		c = 0;
		while (mi < 7 && mj < 7 && board[mi][mj] == oplayer)
		{
			mi++;
			mj++;
			c++;
		}
		if (mi <= 7 && mj <= 7 && board[mi][mj] == player && c>0)
		{
			return true;
		}

		//when all hopes fade away
		return false;
	}

	std::vector<std::vector<int>> BoardHelper::getNewBoardAfterMove(std::vector<std::vector<int>> &board, Point *move, int player)
	{
		//get clone of old board
        vector<vector<int>> newboard (8, vector<int> (8, 0));
		std::vector<std::vector<int>> newboard = RectangularVectors::RectangularIntVector(8, 8);
		for (int k = 0; k < 8; k++)
		{
			for (int l = 0; l < 8; l++)
			{
				newboard[k][l] = board[k][l];
			}
		}

		//place piece
		newboard[move->x][move->y] = player;
		//reverse pieces
		std::vector<Point*> rev = BoardHelper::getReversePoints(newboard,player,move->x,move->y);
		for (auto pt : rev)
		{
			newboard[pt->x][pt->y] = player;
		}

		return newboard;
	}

	std::vector<Point*> BoardHelper::getStableDisks(std::vector<std::vector<int>> &board, int player, int i, int j)
	{

		std::vector<Point*> stableDiscs;

		int mi, mj;
		int oplayer = ((player == 1) ? 2 : 1);

		//move up
		std::vector<Point*> mupts;
		mi = i - 1;
		mj = j;
		while (mi > 0 && board[mi][mj] == player)
		{
			Point tempVar(mi,mj);
			mupts.push_back(&tempVar);
			mi--;
		}
		for (auto sd : mupts)
		{
			bool redundant = false;
			for (auto stableDisc : stableDiscs)
			{
				if (sd->equals(stableDisc))
				{
					redundant = true;
					break;
				}
			}
			if (!redundant)
			{
				stableDiscs.push_back(sd);
			}
		}

		//move down
		std::vector<Point*> mdpts;
		mi = i + 1;
		mj = j;
		while (mi < 7 && board[mi][mj] == oplayer)
		{
			Point tempVar2(mi,mj);
			mdpts.push_back(&tempVar2);
			mi++;
		}
		for (auto sd : mdpts)
		{
			bool redundant = false;
			for (auto stableDisc : stableDiscs)
			{
				if (sd->equals(stableDisc))
				{
					redundant = true;
					break;
				}
			}
			if (!redundant)
			{
				stableDiscs.push_back(sd);
			}
		}

		//move left
		std::vector<Point*> mlpts;
		mi = i;
		mj = j - 1;
		while (mj > 0 && board[mi][mj] == oplayer)
		{
			Point tempVar3(mi,mj);
			mlpts.push_back(&tempVar3);
			mj--;
		}
		for (auto sd : mlpts)
		{
			bool redundant = false;
			for (auto stableDisc : stableDiscs)
			{
				if (sd->equals(stableDisc))
				{
					redundant = true;
					break;
				}
			}
			if (!redundant)
			{
				stableDiscs.push_back(sd);
			}
		}

		//move right
		std::vector<Point*> mrpts;
		mi = i;
		mj = j + 1;
		while (mj < 7 && board[mi][mj] == oplayer)
		{
			Point tempVar4(mi,mj);
			mrpts.push_back(&tempVar4);
			mj++;
		}
		for (auto sd : mrpts)
		{
			bool redundant = false;
			for (auto stableDisc : stableDiscs)
			{
				if (sd->equals(stableDisc))
				{
					redundant = true;
					break;
				}
			}
			if (!redundant)
			{
				stableDiscs.push_back(sd);
			}
		}

		//move up left
		std::vector<Point*> mulpts;
		mi = i - 1;
		mj = j - 1;
		while (mi > 0 && mj > 0 && board[mi][mj] == oplayer)
		{
			Point tempVar5(mi,mj);
			mulpts.push_back(&tempVar5);
			mi--;
			mj--;
		}
		for (auto sd : mulpts)
		{
			bool redundant = false;
			for (auto stableDisc : stableDiscs)
			{
				if (sd->equals(stableDisc))
				{
					redundant = true;
					break;
				}
			}
			if (!redundant)
			{
				stableDiscs.push_back(sd);
			}
		}

		//move up right
		std::vector<Point*> murpts;
		mi = i - 1;
		mj = j + 1;
		while (mi > 0 && mj < 7 && board[mi][mj] == oplayer)
		{
			Point tempVar6(mi,mj);
			murpts.push_back(&tempVar6);
			mi--;
			mj++;
		}
		for (auto sd : murpts)
		{
			bool redundant = false;
			for (auto stableDisc : stableDiscs)
			{
				if (sd->equals(stableDisc))
				{
					redundant = true;
					break;
				}
			}
			if (!redundant)
			{
				stableDiscs.push_back(sd);
			}
		}

		//move down left
		std::vector<Point*> mdlpts;
		mi = i + 1;
		mj = j - 1;
		while (mi < 7 && mj>0 && board[mi][mj] == oplayer)
		{
			Point tempVar7(mi,mj);
			mdlpts.push_back(&tempVar7);
			mi++;
			mj--;
		}
		for (auto sd : mdlpts)
		{
			bool redundant = false;
			for (auto stableDisc : stableDiscs)
			{
				if (sd->equals(stableDisc))
				{
					redundant = true;
					break;
				}
			}
			if (!redundant)
			{
				stableDiscs.push_back(sd);
			}
		}

		//move down right
		std::vector<Point*> mdrpts;
		mi = i + 1;
		mj = j + 1;
		while (mi < 7 && mj < 7 && board[mi][mj] == oplayer)
		{
			Point tempVar8(mi,mj);
			mdrpts.push_back(&tempVar8);
			mi++;
			mj++;
		}
		for (auto sd : mdrpts)
		{
			bool redundant = false;
			for (auto stableDisc : stableDiscs)
			{
				if (sd->equals(stableDisc))
				{
					redundant = true;
					break;
				}
			}
			if (!redundant)
			{
				stableDiscs.push_back(sd);
			}
		}

		return stableDiscs;
	}

	std::vector<Point*> BoardHelper::getFrontierSquares(std::vector<std::vector<int>> &board, int player)
	{

		std::vector<Point*> frontiers;

		int oplayer = ((player == 1) ? 2 : 1);

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] == oplayer)
				{

					std::vector<Point*> possiblefrontiers;

					//check 8 directions

					//up
					if (i > 0 && board[i - 1][j] == 0)
					{
						Point tempVar(i - 1,j);
						possiblefrontiers.push_back(&tempVar);
					}
					//down
					if (i < 7 && board[i + 1][j] == 0)
					{
						Point tempVar2(i + 1,j);
						possiblefrontiers.push_back(&tempVar2);
					}
					//right
					if (j < 7 && board[i][j + 1] == 0)
					{
						Point tempVar3(i,j + 1);
						possiblefrontiers.push_back(&tempVar3);
					}
					//left
					if (j > 0 && board[i][j - 1] == 0)
					{
						Point tempVar4(i,j - 1);
						possiblefrontiers.push_back(&tempVar4);
					}
					//up-left
					if (i > 0 && j > 0 && board[i - 1][j - 1] == 0)
					{
						Point tempVar5(i - 1,j - 1);
						possiblefrontiers.push_back(&tempVar5);
					}
					//up-right
					if (i > 0 && j < 7 && board[i - 1][j + 1] == 0)
					{
						Point tempVar6(i - 1,j + 1);
						possiblefrontiers.push_back(&tempVar6);
					}
					//down-left
					if (i < 7 && j>0 && board[i + 1][j - 1] == 0)
					{
						Point tempVar7(i + 1,j - 1);
						possiblefrontiers.push_back(&tempVar7);
					}
					//down-right
					if (i < 7 && j < 7 && board[i + 1][j + 1] == 0)
					{
						Point tempVar8(i + 1,j + 1);
						possiblefrontiers.push_back(&tempVar8);
					}

					//remove duplicates
					for (auto pf : possiblefrontiers)
					{
						bool redundant = false;
						for (auto f : frontiers)
						{
							if (f->equals(pf))
							{
								redundant = true;
								break;
							}
						}
						if (!redundant)
						{
							frontiers.push_back(pf);
						}
					}
				}
			}
		}

		return frontiers;
	}
}
