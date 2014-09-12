#include "Theme.hpp"

namespace gui
{

template <class T>
OptionsBox<T>::OptionsBox():
	m_current_index(-1),
	m_box(Box::Input),
	m_arrow_left(Arrow(Arrow::Left)),
	m_arrow_right(Arrow(Arrow::Right))
{
	// Build visual components
	m_box.item().setFont(Theme::getFont());
	m_box.item().setCharacterSize(Theme::textSize);
	m_box.setSize(Theme::minWidgetWidth, Theme::getBoxHeight());

	// Pack left arrow
	m_arrow_left.setSize(Theme::getBoxHeight(), Theme::getBoxHeight());
	m_arrow_left.centerItem(m_arrow_left.item());

	// Pack right arrow
	m_arrow_right.setSize(Theme::getBoxHeight(), Theme::getBoxHeight());
	m_arrow_right.setPosition(m_box.getSize().x - Theme::getBoxHeight(), 0);
	m_arrow_right.centerItem(m_arrow_right.item());

	// Widget local bounds
	setSize(m_box.getSize());
}


template <class T>
void OptionsBox<T>::addItem(const sf::String& label, const T& value, bool select)
{
	m_items.push_back(Item(label, value));

	m_box.item().setString(label);
	int width = m_box.item().getLocalBounds().width + Theme::getBoxHeight() * 2 + Theme::PADDING * 2;
	// Check if box needs to be resized
	if (width > getSize().x)
	{
		m_box.setSize(width, Theme::getBoxHeight());
		m_arrow_right.setPosition(width - Theme::getBoxHeight(), 0);
		m_arrow_right.centerItem(m_arrow_right.item());
		setSize(m_box.getSize());
	}

	selectItem(m_items.size() - 1);
}


template <class T>
void OptionsBox<T>::selectItem(size_t item_index)
{
	if (item_index < m_items.size())
	{
		m_current_index = item_index;
		m_box.item().setString(m_items[item_index].label);
		m_box.centerText(m_box.item());
	}
}


template <class T>
const T& OptionsBox<T>::getSelectedValue() const
{
	return m_items[m_current_index].value;
}


template <class T>
size_t OptionsBox<T>::getSelectedIndex() const
{
	return m_current_index;
}


template <class T>
void OptionsBox<T>::selectNext()
{
	if (m_items.size() > 1)
	{
		// Get next item index
		selectItem(m_current_index == (m_items.size() - 1) ? 0 : m_current_index + 1);
		triggerCallback();
	}
}


template <class T>
void OptionsBox<T>::selectPrevious()
{
	if (m_items.size() > 1)
	{
		// Get previous item index
		selectItem(m_current_index == 0 ? m_items.size() - 1 : m_current_index - 1);
		triggerCallback();
	}
}


template <class T>
void OptionsBox<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_box, states);
	target.draw(m_arrow_left, states);
	target.draw(m_arrow_right, states);
}


template <class T>
void OptionsBox<T>::updateArrow(ItemBox<Arrow>& arrow, float x, float y)
{
	if (arrow.containsPoint(x, y))
	{
		if (getState() == StatePressed)
			arrow.press();
		else
			arrow.applyState(StateHovered);
	}
	else
	{
		arrow.applyState(isFocused() ? StateFocused : StateDefault);
	}
}


// callbacks -------------------------------------------------------------------

template <class T>
void OptionsBox<T>::onStateChanged(State state)
{
	// Hovered state is handled in the onMouseMoved callback
	if (state == StateDefault || state == StateFocused)
	{
		m_arrow_left.applyState(state);
		m_arrow_right.applyState(state);
		m_box.applyState(state);
	}
}


template <class T>
void OptionsBox<T>::onMouseMoved(float x, float y)
{
	updateArrow(m_arrow_left, x, y);
	updateArrow(m_arrow_right, x, y);
}


template <class T>
void OptionsBox<T>::onMousePressed(float x, float y)
{
	if (m_arrow_left.containsPoint(x, y))
		m_arrow_left.press();

	else if (m_arrow_right.containsPoint(x, y))
		m_arrow_right.press();
}


template <class T>
void OptionsBox<T>::onMouseReleased(float x, float y)
{
	if (m_arrow_left.containsPoint(x, y))
	{
		selectPrevious();
		m_arrow_left.release();
	}
	else if (m_arrow_right.containsPoint(x, y))
	{
		selectNext();
		m_arrow_right.release();
	}
}


template <class T>
void OptionsBox<T>::onKeyPressed(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Left)
	{
		selectPrevious();
		m_arrow_left.press();
	}
	else if (key == sf::Keyboard::Right)
	{
		selectNext();
		m_arrow_right.press();
	}
}


template <class T>
void OptionsBox<T>::onKeyReleased(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Left)
	{
		m_arrow_left.release();
	}
	else if (key == sf::Keyboard::Right)
	{
		m_arrow_right.release();
	}
}


template <class T>
OptionsBox<T>::Item::Item(const sf::String& string, const T& val):
	label(string),
	value(val)
{
}

}
