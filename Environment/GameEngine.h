#pragma once

namespace game
{

	//interface that gui speaks to
	class GameEngine
	{

	public:
		virtual int getBoardValue(int i, int j) = 0;

		virtual void setBoardValue(int i, int j, int value) = 0;

		virtual void handleClick(int i, int j) = 0;

	};

}
