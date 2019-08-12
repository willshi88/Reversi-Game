#pragma once

#include <string>
#include <vector>

namespace game
{


	class GamePlayer
	{

	protected:
		int myMark = 0;
	public:
		GamePlayer(int mark);

		virtual bool isUserPlayer() = 0;

		virtual std::wstring playerName() = 0;

		virtual Point *play(std::vector<std::vector<int>> &board) = 0;

	};

}
