#include "Arrow.hpp"
#include "../Theme.hpp"

namespace gui
{

Arrow::Arrow(Direction direction):
	m_direction(direction)
{
	const sf::IntRect& rect = Theme::getArrowTextureRect();
	m_vertices[0].texCoords = sf::Vector2f(rect.left,              rect.top);
	m_vertices[1].texCoords = sf::Vector2f(rect.left + rect.width, rect.top);
	m_vertices[2].texCoords = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
	m_vertices[3].texCoords = sf::Vector2f(rect.left,              rect.top + rect.height);

	updateGeometry(0, 0, direction);
}


void Arrow::setColor(const sf::Color& color)
{
	for (int i = 0; i < 4; ++i)
		m_vertices[i].color = color;
}


void Arrow::setPosition(float x, float y)
{
	updateGeometry(x, y, m_direction);
}


void Arrow::move(float dx, float dy)
{
	for (int i = 0; i < 4; ++i)
	{
		m_vertices[i].position.x += dx;
		m_vertices[i].position.y += dy;
	}
}


sf::Vector2f Arrow::getSize() const
{
	const sf::IntRect& rect = Theme::getArrowTextureRect();
	return sf::Vector2f(rect.width, rect.height);
}


void Arrow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &Theme::getTexture();
	target.draw(m_vertices, 4, sf::Quads, states);
}


void Arrow::updateGeometry(float x, float y, Direction direction)
{
	const sf::IntRect& rect = Theme::getArrowTextureRect();
	switch (direction)
	{
		case Top:
			m_vertices[0].position = sf::Vector2f(x,              y);
			m_vertices[1].position = sf::Vector2f(x + rect.width, y);
			m_vertices[2].position = sf::Vector2f(x + rect.width, y + rect.height);
			m_vertices[3].position = sf::Vector2f(x,              y + rect.height);
			break;
		case Bottom:
			m_vertices[0].position = sf::Vector2f(x + rect.width, y + rect.height);
			m_vertices[1].position = sf::Vector2f(x,              y + rect.height);
			m_vertices[2].position = sf::Vector2f(x,              y);
			m_vertices[3].position = sf::Vector2f(x + rect.width, y);
			break;
		case Left:
			m_vertices[0].position = sf::Vector2f(x,               y + rect.width);
			m_vertices[1].position = sf::Vector2f(x,               y);
			m_vertices[2].position = sf::Vector2f(x + rect.height, y);
			m_vertices[3].position = sf::Vector2f(x + rect.height, y + rect.width);
			break;
		case Right:
			m_vertices[0].position = sf::Vector2f(x + rect.height, y);
			m_vertices[1].position = sf::Vector2f(x + rect.height, y + rect.width);
			m_vertices[2].position = sf::Vector2f(x,               y + rect.width);
			m_vertices[3].position = sf::Vector2f(x,               y);
			break;
	}
	m_direction = direction;
}

}
