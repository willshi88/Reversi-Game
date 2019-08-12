#pragma once

#include <vector>

namespace game
{


	class BoardHelper
	{

	public:
		static bool isGameFinished(std::vector<std::vector<int>> &board);


		static std::vector<std::vector<int>> getStartBoard();

		static Point *getMove(std::vector<std::vector<int>> &before, std::vector<std::vector<int>> &after);

		static int getWinner(std::vector<std::vector<int>> &board);

		static int getTotalStoneCount(std::vector<std::vector<int>> &board);

		static int getPlayerStoneCount(std::vector<std::vector<int>> &board, int player);


		static bool hasAnyMoves(std::vector<std::vector<int>> &board, int player);

		static std::vector<Point*> getAllPossibleMoves(std::vector<std::vector<int>> &board, int player);

		static std::vector<Point*> getReversePoints(std::vector<std::vector<int>> &board, int player, int i, int j);

		static bool canPlay(std::vector<std::vector<int>> &board, int player, int i, int j);

		static std::vector<std::vector<int>> getNewBoardAfterMove(std::vector<std::vector<int>> &board, Point *move, int player);

		static std::vector<Point*> getStableDisks(std::vector<std::vector<int>> &board, int player, int i, int j);


		static std::vector<Point*> getFrontierSquares(std::vector<std::vector<int>> &board, int player);

	};

}
