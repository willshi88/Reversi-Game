#include "GreedyPlayer.h"
#include "../game/BoardHelper.h"

namespace player
{
	using namespace game;

	GreedyPlayer::GreedyPlayer(int mark) : GamePlayer(mark)
	{
	}

	bool GreedyPlayer::isUserPlayer()
	{
		return false;
	}

	std:: string GreedyPlayer::playerName()
	{
		return "Greedy Player";
	}

	Point *GreedyPlayer::play(std::vector<std::vector<int>> &board)
	{

		std::vector<Point*> myPossibleMoves = BoardHelper::getAllPossibleMoves(board,myMark);

		Point *bestMove = nullptr;
		int bestValue = 0;

		for (auto move : myPossibleMoves)
		{
			int val = BoardHelper::getReversePoints(board, myMark, move->x,move->y).size();
			if (val > bestValue)
			{
				bestValue = val;
				bestMove = move;
			}
		}

		return bestMove;

	}
}
