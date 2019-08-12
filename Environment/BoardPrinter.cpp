#include "BoardPrinter.h"
#include "BoardCell.h"

namespace game
{

	BoardPrinter::BoardPrinter(std::vector<std::vector<int>> &board, const std::wstring &title)
	{

		this->board = board;

		JPanel *reversiBoard = new JPanel();
		GridLayout tempVar(8,8);
		reversiBoard->setLayout(&tempVar);
		Dimension tempVar2(250,250);
		reversiBoard->setPreferredSize(&tempVar2);
		Color tempVar3(41,100, 59);
		reversiBoard->setBackground(&tempVar3);

		//init board
		//resetBoard();


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

		this->add(reversiBoard);
		this->setTitle(title);
		
		this->pack();
		this->setVisible(true);

		reversiBoard->repaint();
		


	}

	void BoardPrinter::showForm()
	{

	}

	int BoardPrinter::getBoardValue(int i, int j)
	{
		return board[i][j];
	}

	void BoardPrinter::setBoardValue(int i, int j, int value)
	{
		System::err::println(L"Printer cant edit !");
	}

	void BoardPrinter::handleClick(int i, int j)
	{
		//do nothing
	}
}
