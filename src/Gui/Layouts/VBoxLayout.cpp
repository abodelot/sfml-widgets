#include "VBoxLayout.hpp"
#include "../Theme.hpp"

namespace gui
{

void VBoxLayout::recomputeGeometry()
{
    sf::Vector2f pos;
    sf::Vector2f size;
    for (Widget* w = getFirstWidget(); w != nullptr; w = w->m_next)
    {
        w->setPosition(pos);
        pos.y += w->getSize().y + Theme::MARGIN;

        // Layout's width is the wider widget's width
        if (w->getSize().x > size.x)
            size.x = w->getSize().x;
    }
    size.y = pos.y - Theme::MARGIN;
    Widget::setSize(size);
}

}
