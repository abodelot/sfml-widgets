#include "Menu.hpp"
#include "Theme.hpp"

namespace gui
{

Menu::Menu(sf::RenderTarget& window):
	m_window(window),
	m_triggered(NULL)
{
}


int Menu::onEvent(const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::MouseMoved:
	{
		sf::Vector2f mouse = convertMousePosition(event.mouseMove.x, event.mouseMove.y);
		onMouseMoved(mouse.x, mouse.y);
		break;
	}

	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f mouse = convertMousePosition(event.mouseButton.x, event.mouseButton.y);
			onMousePressed(mouse.x, mouse.y);
		}
		break;

	case sf::Event::MouseButtonReleased:
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f mouse = convertMousePosition(event.mouseButton.x, event.mouseButton.y);
			onMouseReleased(mouse.x, mouse.y);
		}
		break;

	case sf::Event::MouseWheelMoved:
		onMouseWheelMoved(event.mouseWheel.delta);
		break;

	case sf::Event::KeyPressed:
		onKeyPressed(event.key.code);
		break;

	case sf::Event::KeyReleased:
		onKeyReleased(event.key.code);
		break;

	case sf::Event::TextEntered:
		onTextEntered(event.text.unicode);
		break;

	default:
		break;
	}

	if (m_triggered != NULL)
	{
		int id = m_triggered->getID();
		m_triggered = NULL;
		return id;
	}
	return -1;
}


void Menu::triggerCallback(const Widget* widget)
{
	m_triggered = widget;
}


sf::Vector2f Menu::convertMousePosition(int x, int y) const
{
	sf::Vector2f mouse = m_window.mapPixelToCoords(sf::Vector2i(x, y));
	mouse -= getPosition();
	return mouse;
}

}
