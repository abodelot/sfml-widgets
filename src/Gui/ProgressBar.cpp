#include "ProgressBar.hpp"
#include "Theme.hpp"

namespace gui
{

const sf::Color BAR_COLOR = sf::Color(0x93, 0xd2, 0x40);

ProgressBar::ProgressBar(float width):
	m_box(Box::Input),
	m_value(0.f)
{
	m_box.setSize(width, Theme::getBoxHeight());
	m_text.setFont(Theme::getFont());
	m_text.setColor(Theme::input.textColor);
	m_text.setCharacterSize(Theme::textSize);

	// Build bar
	m_bar[0].position = sf::Vector2f(Theme::borderSize, Theme::borderSize);
	m_bar[1].position = sf::Vector2f(Theme::borderSize, Theme::borderSize);
	m_bar[2].position = sf::Vector2f(Theme::borderSize, Theme::getBoxHeight() - Theme::borderSize);
	m_bar[3].position = sf::Vector2f(Theme::borderSize, Theme::getBoxHeight() - Theme::borderSize);
	for (int i = 0; i < 4; ++i)
		m_bar[i].color = BAR_COLOR;

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
	target.draw(m_bar, 4, sf::Quads, states);
	target.draw(m_text, states);
}

}
