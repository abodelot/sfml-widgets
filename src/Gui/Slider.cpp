#include "Slider.hpp"
#include "Theme.hpp"

namespace gui
{

Slider::Slider(float length, Orientation orientation):
    m_orientation(orientation),
    m_step(10),
    m_value(0),
    m_box(Box::Input)
{
    int handleHeight = Theme::getBoxHeight();
    int handleWidth = handleHeight / 2;
    int boxHeight = Theme::borderSize * 3;
    int boxOffset = (handleHeight - boxHeight) / 2;

    if (orientation == Horizontal)
    {
        m_box.setSize(length, boxHeight);
        m_box.setPosition(0, boxOffset);
        m_handle.setSize(handleWidth, handleHeight);

        setSize(length, handleHeight);

        for (int i = 0; i < 4; ++i)
        {
            m_progression[i].color = Theme::windowBgColor;
            m_progression[i].position.x = m_box.getPosition().x + Theme::borderSize;
            m_progression[i].position.y = m_box.getPosition().y + Theme::borderSize;
        }
        m_progression[2].position.y += m_box.getSize().y - Theme::borderSize * 2;
        m_progression[3].position.y += m_box.getSize().y - Theme::borderSize * 2;
    }
    else
    {
        m_box.setSize(boxHeight, length);
        m_box.setPosition(boxOffset, 0);
        m_handle.setSize(handleHeight, handleWidth);

        setSize(handleHeight, length);

        for (int i = 0; i < 4; ++i)
        {
            m_progression[i].color = Theme::windowBgColor;
            m_progression[i].position.x = m_box.getPosition().x + Theme::borderSize;
            m_progression[i].position.y = m_box.getSize().y - Theme::borderSize;
        }
        m_progression[1].position.x += m_box.getSize().x - Theme::borderSize * 2;
        m_progression[2].position.x += m_box.getSize().x - Theme::borderSize * 2;
    }
    updateHandlePosition();
}


int Slider::getStep() const
{
    return m_step;
}


void Slider::setStep(int step)
{
    if (step > 0 && step < 100)
        m_step = step;
}


int Slider::getValue() const
{
    return m_value;
}


void Slider::setValue(int value)
{
    // Ensure value is in bounds
    if (value < 0)
        value = 0;
    else if (value > 100)
        value = 100;
    else
    {
        // Round value to the closest step multiple
        int temp = value + m_step / 2;
        value = temp - temp % m_step;
    }

    // If value has changed
    if (value != m_value)
    {
        m_value = value;
        triggerCallback();
        // Move the handle on the slider
        updateHandlePosition();
    }
}


void Slider::updateHandlePosition()
{
    if (m_orientation == Horizontal)
    {
        int max = getSize().x - m_handle.getSize().x - Theme::borderSize * 2;
        int x = max * m_value / 100 + Theme::borderSize;
        m_handle.setPosition(x, 0);
        m_progression[1].position.x = x;
        m_progression[2].position.x = x;
    }
    else
    {
        int max = getSize().y - m_handle.getSize().y - Theme::borderSize * 2;
        int reverse_value = 100 - m_value;
        int y = max * reverse_value / 100 + Theme::borderSize;
        m_handle.setPosition(0, y);
        m_progression[0].position.y = y;
        m_progression[1].position.y = y;
    }
}


void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_box, states);
    target.draw(m_progression, 4, sf::Quads, states);
    target.draw(m_handle, states);
}


// callbacks ------------------------------------------------------------------

void Slider::onKeyPressed(const sf::Event::KeyEvent& key)
{
    switch (key.code)
    {
    case sf::Keyboard::Left:
        setValue(m_value - m_step);
        break;
    case sf::Keyboard::Right:
        setValue(m_value + m_step);
        break;
    case sf::Keyboard::Home:
        setValue(0);
        break;
    case sf::Keyboard::End:
        setValue(100);
        break;
    default:
        break;
    }
}


void Slider::onMousePressed(float x, float y)
{
    if (m_orientation == Horizontal)
        setValue(100 * x / getSize().x);
    else
        setValue(100 - (100 * (y) / getSize().y));

    m_handle.press();
}


void Slider::onMouseMoved(float x, float y)
{
    if (getState() == StateFocused)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (m_orientation == Horizontal)
                setValue(100 * x / getSize().x);
            else
                setValue(100 - (100 * y / getSize().y));
        }
    }
    else if (m_handle.containsPoint(x, y))
    {
        m_handle.applyState(StateHovered);
    }
    else
    {
        m_handle.applyState(StateDefault);
    }
}


void Slider::onMouseReleased(float, float)
{
    m_handle.release();
}


void Slider::onMouseWheelMoved(int delta)
{
    setValue(m_value + (delta > 0 ? m_step : -m_step));
}


void Slider::onStateChanged(State state)
{
    if (state == StateFocused || state == StateDefault)
    {
        m_handle.applyState(state);
    }
}

}
