#pragma once

#include "../../game/GamePlayer.h"
#include <string>
#include <vector>
#include <iostream>
#include <limits>

namespace player { namespace ai { class Evaluator; } }
namespace player { namespace ai { class OpeningBook; } }

namespace player
{
	namespace ai
	{

		using GamePlayer = game::GamePlayer;


		class AIPlayerRealtimeKiller : public GamePlayer
		{

		private:
			int searchDepth = 0;
			Evaluator *evaluator;
			bool isFirstPlayer = false;

			std::vector<Point*> moveHistory;
			std::vector<std::vector<int>> lastboard;
			bool firstRun = true;

		public:
			OpeningBook *OB;
		private:
			bool isOpeningActive = true;

		public:
			virtual ~AIPlayerRealtimeKiller()
			{
				delete evaluator;
				delete OB;
			}

			AIPlayerRealtimeKiller(int mark, int depth, bool firstplayer);

			bool isUserPlayer() override;

			std:: string playerName() override;

			Point *play(std::vector<std::vector<int>> &board) override;

			virtual Point *playUtil(std::vector<std::vector<int>> &board);
		};

	}
}
