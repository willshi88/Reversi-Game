#pragma once

#include "../game/GamePlayer.h"
#include <string>
#include <vector>

namespace player
{

	using GamePlayer = game::GamePlayer;


	class HumanPlayer : public GamePlayer
	{

	public:
		HumanPlayer(int mark);

		bool isUserPlayer() override;

		std:: string playerName() override;

		Point *play(std::vector<std::vector<int>> &board) override;

	};

}
