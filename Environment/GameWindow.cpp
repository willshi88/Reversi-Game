#include "GameWindow.h"
#include "GamePanel.h"

namespace game
{

	GameWindow::GameWindow()
	{
		GamePanel *gp = new GamePanel();
		this->add(gp);
		this->setTitle(L"Reversi v0.1");
		this->setDefaultCloseOperation(WindowConstants::EXIT_ON_CLOSE);
		this->pack();
		this->setVisible(true);
		//this.setSize(500,500);

//JAVA TO C++ CONVERTER TODO TASK: A 'delete gp' statement was not added since gp was passed to a method or constructor. Handle memory management manually.
	}

	void GameWindow::main(std::vector<std::wstring> &args)
	{
		new GameWindow();
	}
}
