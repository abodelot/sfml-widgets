#include "Box.hpp"
#include "../Theme.hpp"


namespace gui
{

Box::Box(Type type):
	m_type(type),
	m_state(StatePressed)
{
	applyState(StateDefault);
}

// Geometry --------------------------------------------------------------------


const sf::Vector2f& Box::getPosition() const
{
	return m_vertices[TOP_LEFT].position;
	//return m_background[0].position;
}


void Box::setPosition(float x, float y)
{
	sf::Vector2f diff = sf::Vector2f(x, y) - getPosition();
	for (size_t i = 0; i < VERTEX_COUNT; ++i)
		m_vertices[i].position += diff;

	/*for (int i = 0; i < 4; ++i)
		m_background[i].position += diff;
	for (int i = 0; i < 16; ++i)
		m_borders[i].position += diff;
	*/
}


void Box::setTextureCoords(int index, float x, float y)
{
	index *= 4;
	m_vertices[index].texCoords =   sf::Vector2f(x, y);
	m_vertices[++index].texCoords = sf::Vector2f(x + Theme::borderSize, y);
	m_vertices[++index].texCoords = sf::Vector2f(x + Theme::borderSize, y + Theme::borderSize);
	m_vertices[++index].texCoords = sf::Vector2f(x, y + Theme::borderSize);
}


void Box::setTexturePos(int index, float x, float y, float w, float h)
{
	index *= 4;
	m_vertices[index].position = sf::Vector2f(x, y);
	m_vertices[++index].position = sf::Vector2f(x + w, y);
	m_vertices[++index].position = sf::Vector2f(x + w, y + h);
	m_vertices[++index].position = sf::Vector2f(x, y + h);
}


void Box::setSize(float width, float height)
{
	if (width <= 0 || height <= 0)
		return;

	float innerWidth = width - Theme::borderSize * 2;
	float innerHeight = height - Theme::borderSize * 2;

	setTexturePos(TOP_LEFT,     0, 0, Theme::borderSize, Theme::borderSize);
	setTexturePos(TOP,          Theme::borderSize, 0, innerWidth, Theme::borderSize);
	setTexturePos(TOP_RIGHT,    Theme::borderSize + innerWidth, 0, Theme::borderSize, Theme::borderSize);
	setTexturePos(LEFT,         0, Theme::borderSize, Theme::borderSize, innerHeight);
	setTexturePos(MIDDLE,       Theme::borderSize, Theme::borderSize, innerWidth, innerHeight);
	setTexturePos(RIGHT,        Theme::borderSize + innerWidth, Theme::borderSize, Theme::borderSize, innerHeight);
	setTexturePos(BOTTOM_LEFT,  0, Theme::borderSize + innerHeight, Theme::borderSize, Theme::borderSize);
	setTexturePos(BOTTOM,       Theme::borderSize, Theme::borderSize + innerHeight, innerWidth, Theme::borderSize);
	setTexturePos(BOTTOM_RIGHT, Theme::borderSize + innerWidth, Theme::borderSize + innerHeight, Theme::borderSize, Theme::borderSize);


	/*// Body
	float border = Theme::BORDER_SIZE;

	m_background[0].position = {0.f,   0.f};
	m_background[1].position = {width, 0.f};
	m_background[2].position = {width, height};
	m_background[3].position = {0.f,   height};

	// Borders
	m_borders[0].position = {0.f, 0.f};
	m_borders[1].position = {border, 0.f};
	m_borders[2].position = {border, height - border};
	m_borders[3].position = {0.f, height - border};

	m_borders[4].position = {border, 0.f};
	m_borders[5].position = {width, 0.f};
	m_borders[6].position = {width, border};
	m_borders[7].position = {border, border};

	m_borders[8].position = {width - border, border};
	m_borders[9].position = {width, border};
	m_borders[10].position = {width, height};
	m_borders[11].position = {width - border, height};

	m_borders[12].position = {0.f, height - border};
	m_borders[13].position = {width - border, height - border};
	m_borders[14].position = {width - border, height};
	m_borders[15].position = {0.f, height};*/
}


sf::Vector2f Box::getSize() const
{


	// Bottom right corner - top left corner
	return m_vertices[BOTTOM_RIGHT * 4 + 2].position - getPosition();
	//return m_background[2].position - m_background[0].position;
}


void Box::press()
{
	applyState(StatePressed);
}


void Box::release()
{
	applyState(StateDefault);
}


bool Box::containsPoint(float x, float y) const
{
// TODO:
	return x > m_vertices[0].position.x
		&& x < m_vertices[BOTTOM_RIGHT * 4 + 2].position.x
		&& y > m_vertices[0].position.y
		&& y < m_vertices[BOTTOM_RIGHT * 4 + 2].position.y;

	/*return x >= m_background[0].position.x  // Left
	    && x <= m_background[2].position.x  // Right
	    && y >= m_background[0].position.y  // Top
	    && y <= m_background[2].position.y; // Bottom*/
}

// Visual properties -----------------------------------------------------------

void Box::applyState(State state)
{

	if (state == m_state || (state == StateHovered && m_state == StateFocused))
		return;

	const sf::IntRect& subrect = Theme::getTextureRect(m_type, state);
	float x = subrect.left;
	float y = subrect.top;
	float width = Theme::borderSize;
	float height = Theme::borderSize;

	setTextureCoords(TOP_LEFT,     x,             y);
	setTextureCoords(TOP,          x + width,     y);
	setTextureCoords(TOP_RIGHT,    x + width * 2, y);
	setTextureCoords(LEFT,         x,             y + height);
	setTextureCoords(MIDDLE,       x + width,     y + height);
	setTextureCoords(RIGHT,        x + width * 2, y + height);
	setTextureCoords(BOTTOM_LEFT,  x,             y + height * 2);
	setTextureCoords(BOTTOM,       x + width,     y + height * 2);
	setTextureCoords(BOTTOM_RIGHT, x + width * 2, y + height * 2);

	if (m_state == StatePressed)
	{
		onRelease();
	}
	else if (state == StatePressed)
	{
		onPress();
	}
	m_state = state;
	/*switch (state)
	{
		case StateDefault:
			// Restore default colors
			//setBodyColor(m_type == Click ? Theme::normal.bgColor : Theme::normal.bgColorInput);
			//setBorderColor(Theme::BorderColorLight, Theme::BorderColorDark);

			release();
			break;

        case StateHovered:
			//setBodyColor(m_type == Click ? Theme::hover.bgColor : Theme::hover.bgColorInput);
			//setBorderColor(Theme::BorderColorLight, Theme::BorderColorDark);
			release();
			break;

		case StatePressed:
			press();
			break;

		case StateFocused:
//			setBodyColor(m_type == Click ? Theme::focus.bgColor : Theme::focus.bgColorInput);
	//		setBorderColor(Theme::BorderColorLight, Theme::BorderColorDark);
			release();
			break;

	}*/
}



void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &Theme::getTexture();
	target.draw(m_vertices, VERTEX_COUNT, sf::Quads, states);
	//target.draw(m_background, 4, sf::Quads, states);
	//target.draw(m_borders, 16, sf::Quads, states);
}


/*
void Box::setBodyColor(const sf::Color& color)
{
	for (size_t i = 0; i < 4; ++i)
		m_background[i].color = color;
}


void Box::setBorderColor(const sf::Color& up, const sf::Color& down)
{
	sf::Color first = m_type == Click ? up : down;
	sf::Color second = m_type == Click ? down : up;

	for (size_t i = 0; i < 16; ++i)
	{
		m_borders[i].color = i < 8 ? first : second;
	}
}
*/
//

void Box::centerText(sf::Text& text)
{
	sf::Vector2f size = getSize();
	sf::FloatRect item_size = text.getLocalBounds();
	int x = getPosition().x + (size.x - item_size.width) / 2;
	text.setPosition(x, Theme::borderSize + Theme::PADDING);
}

}
