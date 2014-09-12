#ifndef GUI_MENU_HPP
#define GUI_MENU_HPP

#include <SFML/Graphics.hpp>
#include "Layouts/VBoxLayout.hpp"

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
	int onEvent(const sf::Event& event);

	void triggerCallback(const Widget* widget) override;

private:
	/**
	 * Get mouse cursor relative position
	 * @param x: absolute x position from the event
	 * @param y: absolute y position from the event
	 * @param relative: if not NULL, compute mouse position relative to this widget
	 * @return relative mouse position
	 */
	sf::Vector2f convertMousePosition(int x, int y) const;

	sf::RenderTarget& m_window;
	const Widget*     m_triggered;
};

}

#endif // GUI_MENU_HPP
