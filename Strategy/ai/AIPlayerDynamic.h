#pragma once

#include "../../game/GamePlayer.h"
#include <string>
#include <vector>


namespace player { namespace ai { class Evaluator; } }

namespace player
{
	namespace ai
	{

		using GamePlayer = game::GamePlayer;


		class AIPlayerDynamic : public GamePlayer
		{

		private:
			int searchDepth = 0;
			Evaluator *evaluator;

		public:
			virtual ~AIPlayerDynamic()
			{
				delete evaluator;
			}

			AIPlayerDynamic(int mark, int depth);

			bool isUserPlayer() override;

			std:: string playerName() override;

			Point *play(std::vector<std::vector<int>> &board) override;
		};

	}
}
