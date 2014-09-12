#include "../Theme.hpp"

namespace gui
{

template <class T>
ItemBox<T>::ItemBox(Box::Type type):
	Box(type)
{
	applyState(StateDefault);
}

template <class T>
ItemBox<T>::ItemBox(const T& item, Box::Type type):
	Box(type),
	m_item(item)
{
	applyState(StateDefault);
}


template <class T>
void ItemBox<T>::applyState(State state)
{
	Box::applyState(state);
	switch (state)
	{
		case StateDefault:
			m_item.setColor(m_type == Click ? Theme::click.textColor : Theme::input.textColor);
			break;
		case StateHovered:
			m_item.setColor(m_type == Click ? Theme::click.textColorHover : Theme::input.textColorHover);
			break;
		case StatePressed:
		case StateFocused:
			m_item.setColor(m_type == Click ? Theme::click.textColorFocus : Theme::input.textColorFocus);
			break;

	}
}

template <class T>
void ItemBox<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Box::draw(target, states);
	target.draw(m_item, states);
}

template <class T>
void ItemBox<T>::onPress()
{
	m_item.move(0.f, 1.f);
}

template <class T>
void ItemBox<T>::onRelease()
{
	m_item.move(0.f, -1.f);
}

}
