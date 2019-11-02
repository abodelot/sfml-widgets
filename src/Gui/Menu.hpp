#ifndef GUI_MENU_HPP
#define GUI_MENU_HPP

#include "Layouts/VBoxLayout.hpp"
#include <SFML/Graphics.hpp>

namespace gui
{

class Menu: public gui::VBoxLayout
{
public:
    Menu(sf::RenderTarget& window);

    /**
     * Handle event and send it to widgets
     * @return triggered widget ID, or -1 if none
     */
    void onEvent(const sf::Event& event);

private:
    /**
     * Get mouse cursor relative position
     * @param x: absolute x position from the event
     * @param y: absolute y position from the event
     * @return relative mouse position
     */
    sf::Vector2f convertMousePosition(int x, int y) const;

    sf::RenderTarget& m_window;
};

}

#endif // GUI_MENU_HPP
