#include "Theme.hpp"

namespace gui
{

template <class T>
OptionsBox<T>::OptionsBox():
    m_currentIndex(-1),
    m_box(Box::Input),
    m_arrowLeft(Arrow(Arrow::Left)),
    m_arrowRight(Arrow(Arrow::Right))
{
    // Build visual components
    m_box.item().setFont(Theme::getFont());
    m_box.item().setCharacterSize(Theme::textSize);
    m_box.setSize(Theme::minWidgetWidth, Theme::getBoxHeight());

    // Pack left arrow
    m_arrowLeft.setSize(Theme::getBoxHeight(), Theme::getBoxHeight());
    m_arrowLeft.centerItem(m_arrowLeft.item());

    // Pack right arrow
    m_arrowRight.setSize(Theme::getBoxHeight(), Theme::getBoxHeight());
    m_arrowRight.setPosition(m_box.getSize().x - Theme::getBoxHeight(), 0);
    m_arrowRight.centerItem(m_arrowRight.item());

    // Widget local bounds
    setSize(m_box.getSize());
}


template <class T>
void OptionsBox<T>::addItem(const sf::String& label, const T& value)
{
    m_items.push_back(Item(label, value));

    m_box.item().setString(label);
    int width = m_box.item().getLocalBounds().width + Theme::getBoxHeight() * 2 + Theme::PADDING * 2;
    // Check if box needs to be resized
    if (width > getSize().x)
    {
        m_box.setSize(width, Theme::getBoxHeight());
        m_arrowRight.setPosition(width - Theme::getBoxHeight(), 0);
        m_arrowRight.centerItem(m_arrowRight.item());
        setSize(m_box.getSize());
    }

    selectItem(m_items.size() - 1);
}


template <class T>
void OptionsBox<T>::selectItem(size_t item_index)
{
    if (item_index < m_items.size())
    {
        m_currentIndex = item_index;
        m_box.item().setString(m_items[item_index].label);
        m_box.centerTextHorizontally(m_box.item());
    }
}


template <class T>
const T& OptionsBox<T>::getSelectedValue() const
{
    return m_items[m_currentIndex].value;
}


template <class T>
size_t OptionsBox<T>::getSelectedIndex() const
{
    return m_currentIndex;
}


template <class T>
void OptionsBox<T>::selectNext()
{
    if (m_items.size() > 1)
    {
        // Get next item index
        selectItem(m_currentIndex == (m_items.size() - 1) ? 0 : m_currentIndex + 1);
        triggerCallback();
    }
}


template <class T>
void OptionsBox<T>::selectPrevious()
{
    if (m_items.size() > 1)
    {
        // Get previous item index
        selectItem(m_currentIndex == 0 ? m_items.size() - 1 : m_currentIndex - 1);
        triggerCallback();
    }
}


template <class T>
void OptionsBox<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_box, states);
    target.draw(m_arrowLeft, states);
    target.draw(m_arrowRight, states);
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
        m_arrowLeft.applyState(state);
        m_arrowRight.applyState(state);
        m_box.applyState(state);
    }
}


template <class T>
void OptionsBox<T>::onMouseMoved(float x, float y)
{
    updateArrow(m_arrowLeft, x, y);
    updateArrow(m_arrowRight, x, y);
}


template <class T>
void OptionsBox<T>::onMousePressed(float x, float y)
{
    if (m_arrowLeft.containsPoint(x, y))
        m_arrowLeft.press();

    else if (m_arrowRight.containsPoint(x, y))
        m_arrowRight.press();
}


template <class T>
void OptionsBox<T>::onMouseReleased(float x, float y)
{
    if (m_arrowLeft.containsPoint(x, y))
    {
        selectPrevious();
        m_arrowLeft.release();
    }
    else if (m_arrowRight.containsPoint(x, y))
    {
        selectNext();
        m_arrowRight.release();
    }
}


template <class T>
void OptionsBox<T>::onKeyPressed(const sf::Event::KeyEvent& key)
{
    if (key.code == sf::Keyboard::Left)
    {
        selectPrevious();
        m_arrowLeft.press();
    }
    else if (key.code == sf::Keyboard::Right)
    {
        selectNext();
        m_arrowRight.press();
    }
}


template <class T>
void OptionsBox<T>::onKeyReleased(const sf::Event::KeyEvent& key)
{
    if (key.code == sf::Keyboard::Left)
    {
        m_arrowLeft.release();
    }
    else if (key.code == sf::Keyboard::Right)
    {
        m_arrowRight.release();
    }
}


template <class T>
OptionsBox<T>::Item::Item(const sf::String& string, const T& val):
    label(string),
    value(val)
{
}

}
