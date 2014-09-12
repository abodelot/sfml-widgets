#include "Cross.hpp"
#include "../Theme.hpp"

namespace gui
{

Cross::Cross()
{
	const sf::IntRect& rect = Theme::getCrossTextureRect();
	m_vertices[0].texCoords = sf::Vector2f(rect.left,              rect.top);
	m_vertices[1].texCoords = sf::Vector2f(rect.left + rect.width, rect.top);
	m_vertices[2].texCoords = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
	m_vertices[3].texCoords = sf::Vector2f(rect.left,              rect.top + rect.height);

	updateGeometry(0, 0);
}


void Cross::setPosition(float x, float y)
{
	updateGeometry(x, y);
}


void Cross::move(float dx, float dy)
{
	for (int i = 0; i < 4; ++i)
	{
		m_vertices[i].position.x += dx;
		m_vertices[i].position.y += dy;
	}
}


void Cross::setSize(float size)
{

}


sf::Vector2f Cross::getSize() const
{
	const sf::IntRect& rect = Theme::getCrossTextureRect();
	return sf::Vector2f(rect.width, rect.height);
}


void Cross::setColor(const sf::Color& color)
{
	for (int i = 0; i < 4; ++i)
		m_vertices[i].color = color;
}


void Cross::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &Theme::getTexture();
	target.draw(m_vertices, 4, sf::Quads, states);
}


void Cross::updateGeometry(float x, float y)
{
	const sf::IntRect& rect = Theme::getCrossTextureRect();
	m_vertices[0].position = sf::Vector2f(x,              y);
	m_vertices[1].position = sf::Vector2f(x + rect.width, y);
	m_vertices[2].position = sf::Vector2f(x + rect.width, y + rect.height);
	m_vertices[3].position = sf::Vector2f(x,              y + rect.height);
}

}
