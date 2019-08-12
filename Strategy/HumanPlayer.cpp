#include "HumanPlayer.h"

namespace player
{
	using GamePlayer = game::GamePlayer;

	HumanPlayer::HumanPlayer(int mark) : game::GamePlayer(mark)
	{
	}

	bool HumanPlayer::isUserPlayer()
	{
		return true;
	}

	std:: string HumanPlayer::playerName()
	{
		return "User";
	}

	Point *HumanPlayer::play(std::vector<std::vector<int>> &board)
	{
		return nullptr;
	}
}
