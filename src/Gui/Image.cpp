#include "Image.hpp"

namespace gui
{

Image::Image():
	m_texture(NULL)
{
	setSelectable(false);
}


Image::Image(const sf::Texture& texture):
	m_texture(NULL)
{
	setSelectable(false);
	setTexture(texture);
}


void Image::setTexture(const sf::Texture& texture)
{
	int width = texture.getSize().x;
	int height = texture.getSize().y;
	m_vertices[0].position = m_vertices[0].texCoords = sf::Vector2f(0, 0);
	m_vertices[1].position = m_vertices[1].texCoords = sf::Vector2f(0, height);
	m_vertices[2].position = m_vertices[2].texCoords = sf::Vector2f(width, height);
	m_vertices[3].position = m_vertices[3].texCoords = sf::Vector2f(width, 0);
	m_texture = &texture;

	// Set widget dimensions
	setSize(width, height);
}


void Image::setColor(const sf::Color& color)
{
	for (int i = 0; i < 4; ++i)
		m_vertices[i].color = color;
}


void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_texture != NULL)
	{
		states.transform *= getTransform();
		states.texture = m_texture;
		target.draw(m_vertices, 4, sf::Quads, states);
	}
}

}
