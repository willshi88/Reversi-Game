#pragma once

#include <string>
#include <vector>

namespace game
{


	class GameWindow : public JFrame
	{

	public:
		GameWindow();

		static void main(std::vector<std::wstring> &args);

	};

}
