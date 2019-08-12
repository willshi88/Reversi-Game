#pragma once

#include "../game/GamePlayer.h"
#include <string>
#include <vector>

namespace player
{

	using namespace game;


	class RandomPlayer : public GamePlayer
	{

	public:
		Random *rnd = new Random();

		virtual ~RandomPlayer()
		{
			delete rnd;
		}

		RandomPlayer(int mark);

		bool isUserPlayer() override;

		std:: string playerName() override;

		Point *play(std::vector<std::vector<int>> &board) override;

	};

}
