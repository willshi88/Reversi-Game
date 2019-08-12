#include "RandomPlayer.h"
#include "../game/BoardHelper.h"

namespace player
{
	using namespace game;

	RandomPlayer::RandomPlayer(int mark) : GamePlayer(mark)
	{
	}

	bool RandomPlayer::isUserPlayer()
	{
		return false;
	}

	std:: string RandomPlayer::playerName()
	{
		return "Random Player";
	}

	Point *RandomPlayer::play(std::vector<std::vector<int>> &board)
	{
		std::vector<Point*> myPossibleMoves = BoardHelper::getAllPossibleMoves(board,myMark);

		if (myPossibleMoves.size() > 0)
		{
			return myPossibleMoves[rnd->nextInt(myPossibleMoves.size())];
		}
		else
		{
			return nullptr;
		}

	}
}
