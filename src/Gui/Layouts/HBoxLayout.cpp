#include "HBoxLayout.hpp"
#include "../Theme.hpp"

namespace gui
{

Widget* HBoxLayout::add(Widget* widget, int id)
{
	widget->setID(id);
	push(widget);
	return widget;
}


void HBoxLayout::recomputeGeometry()
{
	sf::Vector2f pos;
	sf::Vector2f size;
	for (Widget* w = getFirstWidget(); w != NULL; w = w->m_next)
	{
		w->setPosition(pos);
		pos.x += w->getSize().x + Theme::MARGIN;

		// Layout's height is the tallest widget's height
		if (w->getSize().y > size.y)
			size.y = w->getSize().y;
	}
	size.x = pos.x - Theme::MARGIN;
	Widget::setSize(size);
}

}
