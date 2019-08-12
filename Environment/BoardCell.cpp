#include "BoardCell.h"
#include "GameEngine.h"

namespace game
{

	BoardCell::BoardCell(GameEngine *ge, JPanel *parent, int i, int j)
	{
		this->ge = ge;
		this->parent = parent;
		this->i = i;
		this->j = j;
		this->addMouseListener(this);
	}

	void BoardCell::paint(Graphics *g)
	{

		int margin_left = this->getWidth() / 10;
		int margin_top = this->getHeight() / 10;

		//draw highlight
		if (highlight == 1)
		{
			Color tempVar(138, 177, 62);
			g->setColor(&tempVar);
			g->fillRect(0,0,this->getWidth(),this->getHeight());
			g->setColor(parent->getBackground());
			g->fillRect(4,4,this->getWidth() - 8,this->getHeight() - 8);
		}
		else if (highlight == 2)
		{
			Color tempVar2(177, 158, 70);
			g->setColor(&tempVar2);
			g->fillRect(0,0,this->getWidth(),this->getHeight());
			g->setColor(parent->getBackground());
			g->fillRect(4,4,this->getWidth() - 8,this->getHeight() - 8);
		}
		else if (highlight == 10)
		{
			Color tempVar3(177, 43, 71);
			g->setColor(&tempVar3);
			g->fillRect(0,0,this->getWidth(),this->getHeight());
		}

		//draw border
		g->setColor(Color::BLACK);
		g->drawRect(0,0,this->getWidth(),this->getHeight());

		//draw piece
		int value = ge->getBoardValue(i,j);
		if (value == 1)
		{
			g->setColor(Color::BLACK);
			g->fillOval(margin_left,margin_top,this->getWidth() - 2 * margin_left,this->getHeight() - 2 * margin_top);
		}
		else if (value == 2)
		{
			g->setColor(Color::WHITE);
			g->fillOval(margin_left,margin_top,this->getWidth() - 2 * margin_left,this->getHeight() - 2 * margin_top);
		}

		if (!text.isEmpty())
		{
			Color tempVar4(255, 255, 0);
			g->setColor(&tempVar4);
			Font *font = g->getFont();
			Font *nfont = new Font(font->getName(),Font::PLAIN,30);
			g->setFont(nfont);

			drawStringInCenterOfRectangle(g,0,0,this->getWidth(),this->getHeight(),text);


		}

		g->setColor(Color(100,100,100));
		g->drawOval(10,10,this.getWidth()-20,this.getHeight()-20);
		JLabel::paint(g);
	}

	void BoardCell::drawStringInCenterOfRectangle(Graphics *g, int x, int y, int w, int h, const std::wstring &text)
	{
		Graphics2D *g2 = static_cast<Graphics2D*>(g);
		Font *bfont = g2->getFont();
		FontRenderContext *context = g2->getFontRenderContext();
		g2->setFont(bfont);
		int textWidth = static_cast<int>(bfont->getStringBounds(text, context).getWidth());
		LineMetrics *ln = bfont->getLineMetrics(text, context);
		int textHeight = static_cast<int>(ln->getAscent() + ln->getDescent());
		int tx = x + (w - textWidth) / 2;
		int ty = static_cast<int>((y + h + textHeight) / 2 - ln->getDescent());
		g2->drawString(text, static_cast<int>(tx), static_cast<int>(ty));
	}

	void BoardCell::mouseClicked(MouseEvent *e)
	{

	}

	void BoardCell::mousePressed(MouseEvent *e)
	{
		ge->handleClick(i,j);
	}

	void BoardCell::mouseReleased(MouseEvent *e)
	{

	}

	void BoardCell::mouseEntered(MouseEvent *e)
	{

	}

	void BoardCell::mouseExited(MouseEvent *e)
	{

	}
}
