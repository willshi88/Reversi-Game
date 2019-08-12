#include "GamePanel.h"
#include "BoardCell.h"
#include "GamePlayer.h"
#include "BoardHelper.h"

namespace game
{
	using namespace player;
	using namespace player::ai;

	int GamePanel::getBoardValue(int i, int j)
	{
		return board[i][j];
	}

	void GamePanel::setBoardValue(int i, int j, int value)
	{
		board[i][j] = value;
	}

	GamePanel::GamePanel()
	{
		this->setBackground(Color::WHITE);
		BorderLayout tempVar();
		this->setLayout(&tempVar);

		JPanel *reversiBoard = new JPanel();
		GridLayout tempVar2(8,8);
		reversiBoard->setLayout(&tempVar2);
		Dimension tempVar3(500,500);
		reversiBoard->setPreferredSize(&tempVar3);
		Color tempVar4(41,100, 59);
		reversiBoard->setBackground(&tempVar4);

		//init board
		resetBoard();

        vector<vector<int>> cells (8, vector<int> (8, 0));
		cells = RectangularVectors::RectangularBoardCellVector(8, 8);
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				cells[i][j] = new BoardCell(this,reversiBoard,i,j);
				reversiBoard->add(cells[i][j]);
			}
		}


		JPanel *sidebar = new JPanel();
		BoxLayout tempVar5(sidebar,BoxLayout::Y_AXIS);
		sidebar->setLayout(&tempVar5);
		Dimension tempVar6(200,0);
		sidebar->setPreferredSize(&tempVar6);

		score1 = new JLabel(L"Score 1");
		score2 = new JLabel(L"Score 2");

		tscore1 = new JLabel(L"Total Score 1");
		tscore2 = new JLabel(L"Total Score 2");

		sidebar->add(score1);
		sidebar->add(score2);

		JLabel tempVar7(L"-----------");
		sidebar->add(&tempVar7);

		sidebar->add(tscore1);
		sidebar->add(tscore2);


		this->add(sidebar,BorderLayout::WEST);
		this->add(reversiBoard);

		//
		updateBoardInfo();
		updateTotalScore();

		//AI Handler Timer
		player1HandlerTimer = new Timer(1000,[&] (ActionEvent *e)
		{
		handleAI(player1);
		player1HandlerTimer->stop();
		manageTurn();
		});

		player2HandlerTimer = new Timer(1000,[&] (ActionEvent *e)
		{
		handleAI(player2);
		player2HandlerTimer->stop();
		manageTurn();
		});

		manageTurn();

	}

	void GamePanel::manageTurn()
	{
		if (BoardHelper::hasAnyMoves(board,1) || BoardHelper::hasAnyMoves(board,2))
		{
			updateBoardInfo();
			if (turn == 1)
			{
				if (BoardHelper::hasAnyMoves(board,1))
				{
					if (player1->isUserPlayer())
					{
						awaitForClick = true;
						//after click this function should be call backed
					}
					else
					{
						player1HandlerTimer->start();
					}
				}
				else
				{
					//forfeit this move and pass the turn
					std::wcout << L"Player 1 has no legal moves !" << std::endl;
					turn = 2;
					manageTurn();
				}
			}
			else
			{
				if (BoardHelper::hasAnyMoves(board,2))
				{
					if (player2->isUserPlayer())
					{
						awaitForClick = true;
						//after click this function should be call backed
					}
					else
					{
						player2HandlerTimer->start();
					}
				}
				else
				{
					//forfeit this move and pass the turn
					std::wcout << L"Player 2 has no legal moves !" << std::endl;
					turn = 1;
					manageTurn();
				}
			}
		}
		else
		{
			//game finished
			std::wcout << L"Game Finished !" << std::endl;
			int winner = BoardHelper::getWinner(board);
			if (winner == 1)
			{
				totalscore1++;
			}
			else if (winner == 2)
			{
				totalscore2++;
			}
			updateTotalScore();
			
		}
	}

	void GamePanel::resetBoard()
	{

        vector<vector<int>> board (8, vector<int> (8, 0));
		board = RectangularVectors::RectangularIntVector(8, 8);
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				board[i][j] = 0;
			}
		}
		//initial board state
		setBoardValue(3,3,2);
		setBoardValue(3,4,1);
		setBoardValue(4,3,1);
		setBoardValue(4,4,2);
	}

	void GamePanel::updateBoardInfo()
	{

		int p1score = 0;
		int p2score = 0;

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] == 1)
				{
					p1score++;
				}
				if (board[i][j] == 2)
				{
					p2score++;
				}

				if (BoardHelper::canPlay(board,turn,i,j))
				{
					cells[i][j]->highlight = 1;
				}
				else
				{
					cells[i][j]->highlight = 0;
				}
			}
		}

		score1->setText(player1->playerName() + L" : " + std::to_wstring(p1score));
		score2->setText(player2->playerName() + L" : " + std::to_wstring(p2score));
	}

	void GamePanel::updateTotalScore()
	{
		tscore1->setText(player1->playerName() + L" : " + std::to_wstring(totalscore1));
		tscore2->setText(player2->playerName() + L" : " + std::to_wstring(totalscore2));
	}

	void GamePanel::handleClick(int i, int j)
	{
		if (awaitForClick && BoardHelper::canPlay(board,turn,i,j))
		{
			std::wcout << L"User Played in : " << i << L" , " << j << std::endl;

			//update board
			Point tempVar(i,j);
			board = BoardHelper::getNewBoardAfterMove(board,&tempVar,turn);

			//advance turn
			turn = (turn == 1) ? 2 : 1;

			repaint();

			awaitForClick = false;

			//callback
			manageTurn();
		}
	}

	void GamePanel::handleAI(GamePlayer *ai)
	{
		Point *aiPlayPoint = ai->play(board);
		int i = aiPlayPoint->x;
		int j = aiPlayPoint->y;
		if (!BoardHelper::canPlay(board,ai->myMark,i,j))
		{
			System::err::println(L"FATAL : AI Invalid Move !");
		}
		std::wcout << ai->playerName() << L" Played in : " << i << L" , " << j << std::endl;

		//update board
		board = BoardHelper::getNewBoardAfterMove(board,aiPlayPoint,turn);

		//advance turn
		turn = (turn == 1) ? 2 : 1;

		repaint();
	}
}
