#pragma once

#include <string>


namespace game { class GameEngine; }

namespace game
{


	class BoardCell : public JLabel, public MouseListener
	{

	public:
		int i = 0;
		int j = 0;

		GameEngine *ge;
		JPanel *parent;

		int highlight = 0;

		std::wstring text = L"";

		virtual ~BoardCell()
		{
			delete ge;
			delete parent;
		}

		BoardCell(GameEngine *ge, JPanel *parent, int i, int j);

		void paint(Graphics *g) override;


		//Extension function to ease drawing text
		virtual void drawStringInCenterOfRectangle(Graphics *g, int x, int y, int w, int h, const std::wstring &text);

		void mouseClicked(MouseEvent *e) override;

		void mousePressed(MouseEvent *e) override;

		void mouseReleased(MouseEvent *e) override;

		void mouseEntered(MouseEvent *e) override;

		void mouseExited(MouseEvent *e) override;
	};

}
