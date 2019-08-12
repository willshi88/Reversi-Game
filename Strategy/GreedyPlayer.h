#pragma once

#include "../game/GamePlayer.h"
#include <string>
#include <vector>

namespace player
{

	using namespace game;


	class GreedyPlayer : public GamePlayer
	{

	public:
		GreedyPlayer(int mark);

		bool isUserPlayer() override;

		std:: string playerName() override;

		Point *play(std::vector<std::vector<int>> &board) override;

	};
}
