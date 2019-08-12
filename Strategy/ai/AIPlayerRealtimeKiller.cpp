#include "AIPlayerRealtimeKiller.h"
#include "Evaluator.h"
#include "OpeningBook.h"
#include "RealtimeEvaluator.h"
#include "../../game/BoardHelper.h"
#include "Minimax.h"

namespace player
{
	namespace ai
	{
		using BoardHelper = game::BoardHelper;
		using GamePlayer = game::GamePlayer;

		AIPlayerRealtimeKiller::AIPlayerRealtimeKiller(int mark, int depth, bool firstplayer) : game::GamePlayer(mark)
		{

			//init OpeningBook
			OB = new OpeningBook();
			OB->initOpening();

			moveHistory = std::vector<Point*>();

			searchDepth = depth;
			isFirstPlayer = firstplayer;

			if (mark == 1)
			{
				evaluator = new RealtimeEvaluator(std::vector<std::vector<int>>
				{
					std::vector<int> {8, 85, -40, 10, 210, 520},
					std::vector<int> {8, 85, -40, 10, 210, 520},
					std::vector<int> {33, -50, -15, 4, 416, 2153},
					std::vector<int> {46, -50, -1, 3, 612, 4141},
					std::vector<int> {51, -50, 62, 3, 595, 3184},
					std::vector<int> {33, -5, 66, 2, 384, 2777},
					std::vector<int> {44, 50, 163, 0, 443, 2568},
					std::vector<int> {13, 50, 66, 0, 121, 986},
					std::vector<int> {4, 50, 31, 0, 27, 192},
					std::vector<int> {8, 500, 77, 0, 36, 299}
				}, std::vector<int> {0, 55, 56, 57, 58, 59, 60, 61, 62, 63});
			}
			else
			{
				evaluator = new RealtimeEvaluator(std::vector<std::vector<int>>
				{
					std::vector<int> {8, 85, -40, 10, 210, 520},
					std::vector<int> {8, 85, -40, 10, 210, 520},
					std::vector<int> {33, -50, -15, 4, 416, 2153},
					std::vector<int> {46, -50, -1, 3, 612, 4141},
					std::vector<int> {51, -50, 62, 3, 595, 3184},
					std::vector<int> {33, -5, 66, 2, 384, 2777},
					std::vector<int> {44, 50, 163, 0, 443, 2568},
					std::vector<int> {13, 50, 66, 0, 121, 986},
					std::vector<int> {4, 50, 31, 0, 27, 192},
					std::vector<int> {8, 500, 77, 0, 36, 299}
				}, std::vector<int> {0, 55, 56, 57, 58, 59, 60, 61, 62, 63});
			}
		}

		bool AIPlayerRealtimeKiller::isUserPlayer()
		{
			return false;
		}

		std:: string AIPlayerRealtimeKiller::playerName()
		{
			return "Realtime Killer (Depth " + std::to_wstring(searchDepth) + ")";
		}

		Point *AIPlayerRealtimeKiller::play(std::vector<std::vector<int>> &board)
		{

			//Add Opponents Move to History (null means opponent was not able to play)
			//Opening loses effect when Move Sequence is out of 1-1 sync
			if (firstRun)
			{
				if (!isFirstPlayer)
				{
					Point *opMove = BoardHelper::getMove(BoardHelper::getStartBoard(),board);
					if (opMove != nullptr)
					{
						moveHistory.push_back(opMove);
					}
					else
					{
						isOpeningActive = false;
					}
				}
				firstRun = false;
			}
			else
			{
				Point *opMove = BoardHelper::getMove(lastboard,board);
				if (opMove != nullptr)
				{
					moveHistory.push_back(opMove);
				}
				else
				{
					isOpeningActive = false;
				}
			}

			Point *myMove = playUtil(board);
			lastboard = BoardHelper::getNewBoardAfterMove(board,myMove,myMark);
			moveHistory.push_back(myMove);

			return myMove;
		}

		Point *AIPlayerRealtimeKiller::playUtil(std::vector<std::vector<int>> &board)
		{
			std::vector<Point*> moves = BoardHelper::getAllPossibleMoves(board,myMark);
			int opMark = ((myMark == 1) ? 2 : 1);

			Point *bestToPlay = nullptr;
			int bestValue = std::numeric_limits<int>::min();

			//Corner Detection
			std::vector<Point*> corners;
			Point tempVar(0,0);
			corners.push_back(&tempVar);
			Point tempVar2(0,7);
			corners.push_back(&tempVar2);
			Point tempVar3(7,0);
			corners.push_back(&tempVar3);
			Point tempVar4(7,7);
			corners.push_back(&tempVar4);
			for (auto move : moves)
			{
				for (auto corner : corners)
				{
					if (corner->equals(move))
					{
						int mval = evaluator->eval(BoardHelper::getNewBoardAfterMove(board,move,myMark),myMark);
						if (mval > bestValue)
						{
							//update best corner
							bestToPlay = move;
							bestValue = mval;
						}
					}
				}
			}
			if (bestToPlay != nullptr)
			{
				std:: cout << "\033[1;30;34m KILLER MOVE : CORNER \033[0m\n" << std::endl;
				return bestToPlay;
			}

			bestToPlay = nullptr;
			bestValue = std::numeric_limits<int>::min();

			//Blocking Move Detection
			for (auto move : moves)
			{
				std::vector<std::vector<int>> resBoard = BoardHelper::getNewBoardAfterMove(board,move,myMark);
				if (BoardHelper::getAllPossibleMoves(resBoard,opMark).empty())
				{ //if opponent has no moves
					int mval = evaluator->eval(resBoard,myMark);
					if (mval > bestValue)
					{
						//update best corner
						bestToPlay = move;
						bestValue = mval;
					}
				}
			}
			if (bestToPlay != nullptr)
			{
				std:: cout << "\033[1;30;34m KILLER MOVE : BLOCKING MOVE \033[0m\n" << std::endl;
				return bestToPlay;
			}

			//Opening Moves (if fails then stop opening)
			if (isOpeningActive)
			{
				Point *opmove = OB->getMoveFromOpeningBook(moveHistory);
				if (opmove != nullptr)
				{
					std:: cout << "\033[1;30;34m OPENING MOVE \033[0m\n" << std::endl;
					return opmove;
				}
				isOpeningActive = false;
				std:: cout << "\033[1;30;44m OPENING DEACTIVATED \033[0m\n" << std::endl;
			}

			//if no killer moves availiable do a minimax search
			return Minimax::solve(board,myMark,searchDepth,evaluator);
		}
	}
}
