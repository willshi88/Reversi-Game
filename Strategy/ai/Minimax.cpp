#include "Minimax.h"
#include "Evaluator.h"
#include "../../game/BoardHelper.h"

namespace player
{
	namespace ai
	{
		using BoardHelper = game::BoardHelper;
		using BoardPrinter = game::BoardPrinter;
int Minimax::nodesExplored = 0;

		Point *Minimax::solve(std::vector<std::vector<int>> &board, int player, int depth, Evaluator *e)
		{
			nodesExplored = 0;
			int bestScore = std::numeric_limits<int>::min();
			Point *bestMove = nullptr;
			for (auto move : BoardHelper::getAllPossibleMoves(board,player))
			{
				//create new node
				std::vector<std::vector<int>> newNode = BoardHelper::getNewBoardAfterMove(board,move,player);
				//recursive call
				int childScore = MMAB(newNode,player,depth - 1,false,std::numeric_limits<int>::min(),std::numeric_limits<int>::max(),e);
					if (childScore > bestScore)
					{
					bestScore = childScore;
					bestMove = move;
					}
			}
			std:: cout << "Nodes Explored : " << nodesExplored << std::endl;
			return bestMove;
		}

		int Minimax::MMAB(std::vector<std::vector<int>> &node, int player, int depth, bool max, int alpha, int beta, Evaluator *e)
		{
			nodesExplored++;
			//if terminal reached or depth limit reached evaluate
			if (depth == 0 || BoardHelper::isGameFinished(node))
			{
				//BoardPrinter bpe = new BoardPrinter(node,"Depth : " + depth);
				return e->eval(node,player);
			}
			int oplayer = (player == 1) ? 2 : 1;
			//if no moves available then forfeit turn
			if ((max && !BoardHelper::hasAnyMoves(node,player)) || (!max && !BoardHelper::hasAnyMoves(node,oplayer)))
			{
				//System.out.println("Forfeit State Reached !");
				return MMAB(node,player,depth - 1,!max,alpha,beta,e);
			}
			int score;
			if (max)
			{
				//maximizing
				score = std::numeric_limits<int>::min();
				for (auto move : BoardHelper::getAllPossibleMoves(node,player))
				{ //my turn
					//create new node
					std::vector<std::vector<int>> newNode = BoardHelper::getNewBoardAfterMove(node,move,player);
					//recursive call
					int childScore = MMAB(newNode,player,depth - 1,false,alpha,beta,e);
					if (childScore > score)
					{
						score = childScore;
					}
					//update alpha
					if (score > alpha)
					{
						alpha = score;
					}
					if (beta <= alpha)
					{
						break; //Beta Cutoff
					}
				}
			}
			else
			{
				//minimizing
				score = std::numeric_limits<int>::max();
				for (auto move : BoardHelper::getAllPossibleMoves(node,oplayer))
				{ //opponent turn
					//create new node
					std::vector<std::vector<int>> newNode = BoardHelper::getNewBoardAfterMove(node,move,oplayer);
					//recursive call
					int childScore = MMAB(newNode,player,depth - 1,true,alpha,beta,e);
					if (childScore < score)
					{
						score = childScore;
					}
					//update beta
					if (score < beta)
					{
						beta = score;
					}
					if (beta <= alpha)
					{
						break; //Alpha Cutoff
					}
				}
			}
			return score;
		}
	}
}
