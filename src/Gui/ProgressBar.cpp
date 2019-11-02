#include "ProgressBar.hpp"
#include "Theme.hpp"

namespace gui
{

ProgressBar::ProgressBar(float width):
    m_box(Box::Input),
    m_value(0.f)
{
    m_box.setSize(width, Theme::getBoxHeight());
    m_text.setFont(Theme::getFont());
    m_text.setFillColor(Theme::input.textColor);
    m_text.setCharacterSize(Theme::textSize);

    // Build bar
    m_bar[0].position = sf::Vector2f(Theme::borderSize, Theme::borderSize);
    m_bar[1].position = sf::Vector2f(Theme::borderSize, Theme::borderSize);
    m_bar[2].position = sf::Vector2f(Theme::borderSize, Theme::getBoxHeight() - Theme::borderSize);
    m_bar[3].position = sf::Vector2f(Theme::borderSize, Theme::getBoxHeight() - Theme::borderSize);

    const sf::IntRect& rect = Theme::getProgressBarTextureRect();
    m_bar[0].texCoords = sf::Vector2f(rect.left, rect.top);
    m_bar[1].texCoords = sf::Vector2f(rect.left + rect.width, rect.top);
    m_bar[2].texCoords = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
    m_bar[3].texCoords = sf::Vector2f(rect.left, rect.top + rect.height);

    setValue(m_value);
    setSelectable(false);
    setSize(m_box.getSize());
}


void ProgressBar::setValue(float value)
{
    float x = Theme::borderSize + (getSize().x - Theme::borderSize * 2) * value / 100;
    m_bar[1].position.x = m_bar[2].position.x = x;

    m_text.setString(std::to_string((int) value) + "%");
    m_box.centerText(m_text);

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
    target.draw(m_text, states);
}

}
