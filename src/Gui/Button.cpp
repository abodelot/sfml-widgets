#include "Button.hpp"
#include "Theme.hpp"

namespace gui
{

Button::Button(const sf::String& string)
{
	m_box.item().setFont(Theme::getFont());
	m_box.item().setCharacterSize(Theme::textSize);
	m_box.setSize(Theme::minWidgetWidth, Theme::getBoxHeight());
	setString(string);
	setSize(m_box.getSize());
}


void Button::setString(const sf::String& string)
{
	m_box.item().setString(string);

	// Recompute widget width
	int fittingWidth = m_box.item().getLocalBounds().width + Theme::PADDING * 2 + Theme::borderSize * 2;
	int width = std::max(fittingWidth, Theme::minWidgetWidth);
	m_box.setSize(width, Theme::getBoxHeight());
	m_box.centerText(m_box.item());
	setSize(m_box.getSize());
}


const sf::String& Button::getString() const
{
	return m_box.item().getString();
}


void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_box, states);
}

// Callbacks -------------------------------------------------------------------

void Button::onStateChanged(State state)
{
	m_box.applyState(state);
}


void Button::onMouseMoved(float x, float y)
{
	if (getState() == StatePressed)
	{
		if (containsPoint(sf::Vector2f(x, y)))
			m_box.press();
		else
			m_box.release();
	}
}


void Button::onMouseReleased(float x, float y)
{
	if (containsPoint({x, y}))
	{
		triggerCallback();
	}
}


void Button::onKeyPressed(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Return)
	{
		triggerCallback();
		m_box.press();
	}
}


void Button::onKeyReleased(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Return)
	{
		m_box.release();
	}
}

}
