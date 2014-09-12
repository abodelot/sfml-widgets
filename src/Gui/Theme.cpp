#include "Theme.hpp"

namespace gui
{

size_t    Theme::textSize = 12;
Theme::Style Theme::click;
Theme::Style Theme::input;
sf::Color Theme::windowBgColor;
int       Theme::borderSize      = 1.f;
int       Theme::minWidgetWidth  = 86;
float     Theme::PADDING          = 1.f;
float     Theme::MARGIN           = 7.f;

sf::Keyboard::Key Theme::nextWidgetKey = sf::Keyboard::Down;
sf::Keyboard::Key Theme::previousWidgetKey = sf::Keyboard::Up;

sf::Font Theme::m_font;
sf::Texture Theme::m_texture;
sf::IntRect Theme::m_subrects[_TEX_COUNT];


bool Theme::loadFont(const std::string& filename)
{
	return m_font.loadFromFile(filename);
}


bool Theme::loadTexture(const std::string& filename)
{
	if (m_texture.loadFromFile(filename))
	{
		sf::IntRect subrect;
		subrect.width = m_texture.getSize().x;
		subrect.height = m_texture.getSize().y / _TEX_COUNT;

		for (int i = 0; i < _TEX_COUNT; ++i)
		{
			m_subrects[i] = subrect;
			subrect.top += subrect.height;
		}

		borderSize = subrect.width / 3;
		return true;
	}
	return false;
}


const sf::Font& Theme::getFont()
{
	return m_font;
}


const sf::Texture& Theme::getTexture()
{
	return m_texture;
}


const sf::IntRect& Theme::getTextureRect(Box::Type type, State state)
{
	TextureID id(BOX_DEFAULT);
	switch (state)
	{
		case StateDefault:
			id = type == Box::Click ? BOX_DEFAULT : BOX_INPUT_DEFAULT;
			break;
		case StateHovered:
			id = type == Box::Click ? BOX_HOVERED : BOX_INPUT_DEFAULT;
			break;
		case StatePressed:
			id = type == Box::Click ? BOX_PRESSED : BOX_INPUT_FOCUSED;
			break;
		case StateFocused:
			id = type == Box::Click ? BOX_FOCUSED : BOX_INPUT_FOCUSED;
			break;
	}
	return m_subrects[id];
}


const sf::IntRect& Theme::getCrossTextureRect()
{
	return m_subrects[CROSS];
}


const sf::IntRect& Theme::getArrowTextureRect()
{
	return m_subrects[ARROW];
}


float Theme::getBoxHeight()
{
	return getLineSpacing() + borderSize * 2 + PADDING * 2;
}


int Theme::getLineSpacing()
{
	return m_font.getLineSpacing(textSize);
}

}
