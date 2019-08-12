#pragma once

#include "GameEngine.h"
#include <string>
#include <vector>


namespace game { class BoardCell; }

namespace game
{


	class BoardPrinter : public JFrame, public GameEngine
	{

	public:
		std::vector<std::vector<BoardCell*>> cells;
		std::vector<std::vector<int>> board;

		BoardPrinter(std::vector<std::vector<int>> &board, const std::wstring &title);

		virtual void showForm();


		int getBoardValue(int i, int j) override;

		void setBoardValue(int i, int j, int value) override;

		void handleClick(int i, int j) override;
	};

}
