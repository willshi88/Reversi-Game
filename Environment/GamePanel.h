#pragma once

#include "GameEngine.h"
#include <vector>
#include <iostream>


namespace game { class BoardCell; }
namespace game { class GamePlayer; }

namespace game
{

	using namespace player;
	using namespace player::ai;


	class GamePanel : public JPanel, public GameEngine
	{

		//reversi board
	public:
		std::vector<std::vector<int>> board;

		//player turn
		//black plays first
		int turn = 1;

		//swing elements
		std::vector<std::vector<BoardCell*>> cells;
		JLabel *score1;
		JLabel *score2;

		int totalscore1 = 0;
		int totalscore2 = 0;

		JLabel *tscore1;
		JLabel *tscore2;


		GamePlayer *player1 = new AIPlayerRealtimeKiller(1,6,true);
		GamePlayer *player2 = new AIPlayerDynamic(2,6);

		Timer *player1HandlerTimer;
		Timer *player2HandlerTimer;

		virtual ~GamePanel()
		{
			delete score1;
			delete score2;
			delete tscore1;
			delete tscore2;
			delete player1;
			delete player2;
			delete player1HandlerTimer;
			delete player2HandlerTimer;
		}

		int getBoardValue(int i, int j) override;

		void setBoardValue(int i, int j, int value) override;

		GamePanel();

	private:
		bool awaitForClick = false;

	public:
		virtual void manageTurn();

		virtual void resetBoard();

		//update highlights on possible moves and scores
		virtual void updateBoardInfo();

		virtual void updateTotalScore();

		void handleClick(int i, int j) override;

		virtual void handleAI(GamePlayer *ai);

	};

}
