#ifndef GUI_MENU_HPP
#define GUI_MENU_HPP

#include "Layouts/VBoxLayout.hpp"
#include <SFML/Graphics.hpp>

namespace gui
{

/**
 * Entry point for the GUI.
 * A Menu is a VBoxLayout with a general onEvent handler
 */
class Menu: public gui::VBoxLayout
{
public:
    Menu(sf::RenderWindow& window);

    /**
     * Handle an SFML event and send it to widgets
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

    /**
     * Update the cursor type on the RenderWindow
     */
    void setMouseCursor(sf::Cursor::Type cursorType) override;

    sf::RenderWindow& m_window;
    sf::Cursor::Type m_cursorType;
};

}

#endif // GUI_MENU_HPP
