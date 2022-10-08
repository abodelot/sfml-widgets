#include "ProgressBar.hpp"
#include "Theme.hpp"

namespace gui
{

ProgressBar::ProgressBar(float length, Orientation orientation, LabelPlacement labelPlacement):
    m_box(Box::Input),
    m_orientation(orientation),
    m_labelPlacement(labelPlacement),
    m_value(0.f)
{
    if (orientation == Horizontal)
    {
        m_box.setSize(length, Theme::getBoxHeight());
    }
    else
    {
        m_box.setSize(Theme::getBoxHeight(), length);
        if (m_labelPlacement == LabelOver)
            m_label.setRotation(90.f);
    }

    m_label.setString("100%");
    m_label.setFont(Theme::getFont());
    m_label.setFillColor(Theme::input.textColor);
    m_label.setCharacterSize(Theme::textSize);

    // Build bar
    const float x1 = Theme::PADDING;
    const float y1 = Theme::PADDING;
    const float x2 = (orientation == Horizontal ? length : Theme::getBoxHeight()) - Theme::PADDING;
    const float y2 = (orientation == Horizontal ? Theme::getBoxHeight() : length) - Theme::PADDING;
    m_bar[0].position = {x1, y1};
    m_bar[1].position = {x2, y1};
    m_bar[2].position = {x2, y2};
    m_bar[3].position = {x1, y2};

    const sf::IntRect& rect = Theme::getProgressBarTextureRect();
    m_bar[0].texCoords = sf::Vector2f(rect.left, rect.top);
    m_bar[1].texCoords = sf::Vector2f(rect.left + rect.width, rect.top);
    m_bar[2].texCoords = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
    m_bar[3].texCoords = sf::Vector2f(rect.left, rect.top + rect.height);

    float labelWidth = m_label.getLocalBounds().width;
    float labelHeight = m_label.getLocalBounds().height;
    if (m_labelPlacement == LabelOutside)
    {
        if (orientation == Horizontal)
        {
            // Place label on the right of the bar
            m_label.setPosition(length + Theme::PADDING, Theme::PADDING);
            setSize(length + Theme::PADDING + labelWidth, m_box.getSize().y);
        }
        else
        {
            // Place label below the bar
            setSize(m_box.getSize().x, length + Theme::PADDING + labelHeight);
        }
    }
    else
    {
        setSize(m_box.getSize());
    }

    setValue(m_value);
    setSelectable(false);
}


void ProgressBar::setValue(float value)
{
    m_label.setString(std::to_string((int)value) + "%");
    if (m_orientation == Horizontal)
    {
        float x = Theme::PADDING + (m_box.getSize().x - Theme::PADDING * 2) * value / 100;
        m_bar[1].position.x = m_bar[2].position.x = x;
        if (m_labelPlacement == LabelOver)
        {
            m_box.centerTextHorizontally(m_label);
        }
    }
    else
    {
        float fullHeight = m_box.getSize().y - Theme::PADDING * 2;
        float y = fullHeight * value / 100;
        m_bar[0].position.y = m_bar[1].position.y = (fullHeight - y) + Theme::PADDING;
        if (m_labelPlacement == LabelOver)
        {
            m_box.centerTextVertically(m_label);
        }
        else if (m_labelPlacement == LabelOutside)
        {
            // Re-center label horizontally (text width can change)
            float labelX = (m_box.getSize().x - m_label.getLocalBounds().width) / 2;
            m_label.setPosition(labelX, m_box.getSize().y + Theme::PADDING);
        }
    }

    m_value = value;
}


float ProgressBar::getValue() const
{
    return m_value;
}


void ProgressBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_box, states);
    states.texture = &Theme::getTexture();
    target.draw(m_bar, 4, sf::Quads, states);
    if (m_labelPlacement != LabelNone)
        target.draw(m_label, states);
}

}
