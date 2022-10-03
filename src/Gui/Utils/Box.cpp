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
}


void Box::setPosition(float x, float y)
{
    sf::Vector2f diff = sf::Vector2f(x, y) - getPosition();
    for (size_t i = 0; i < VERTEX_COUNT; ++i)
        m_vertices[i].position += diff;
}


void Box::setSliceTextureCoords(Slice slice, float x, float y)
{
    int index = slice * 4;
    m_vertices[index].texCoords = sf::Vector2f(x, y);
    m_vertices[++index].texCoords = sf::Vector2f(x + Theme::borderSize, y);
    m_vertices[++index].texCoords = sf::Vector2f(x + Theme::borderSize, y + Theme::borderSize);
    m_vertices[++index].texCoords = sf::Vector2f(x, y + Theme::borderSize);
}


void Box::setSliceGeometry(Slice slice, float x1, float y1, float x2, float y2)
{
    int index = slice * 4;
    m_vertices[index].position = sf::Vector2f(x1, y1);
    m_vertices[++index].position = sf::Vector2f(x2, y1);
    m_vertices[++index].position = sf::Vector2f(x2, y2);
    m_vertices[++index].position = sf::Vector2f(x1, y2);
}


void Box::setSize(float width, float height)
{
    if (width <= 0 || height <= 0)
        return;

    // Move/resize each of the 9 slices
    // 0--x1--x2--x3
    // |   |   |   |
    // y1--+---+---+
    // |   |   |   |
    // y2--+---+---+
    // |   |   |   |
    // y3--+---+---+
    float x1 = Theme::borderSize;
    float x2 = width - Theme::borderSize;
    float x3 = width;
    float y1 = Theme::borderSize;
    float y2 = height - Theme::borderSize;
    float y3 = height;
    setSliceGeometry(TOP_LEFT, 0, 0, x1, y1);
    setSliceGeometry(TOP, x1, 0, x2, y1);
    setSliceGeometry(TOP_RIGHT, x2, 0, x3, y1);
    setSliceGeometry(LEFT, 0, y1, x1, y2);
    setSliceGeometry(MIDDLE, x1, y1, x2, y2);
    setSliceGeometry(RIGHT, x2, y1, x3, y2);
    setSliceGeometry(BOTTOM_LEFT, 0, y2, x1, y3);
    setSliceGeometry(BOTTOM, x1, y2, x2, y3);
    setSliceGeometry(BOTTOM_RIGHT, x2, y2, x3, y3);
}


sf::Vector2f Box::getSize() const
{
    // Bottom right corner - top left corner
    return m_vertices[BOTTOM_RIGHT * 4 + 2].position - getPosition();
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
    return x > m_vertices[0].position.x && x < m_vertices[BOTTOM_RIGHT * 4 + 2].position.x
        && y > m_vertices[0].position.y && y < m_vertices[BOTTOM_RIGHT * 4 + 2].position.y;
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

    setSliceTextureCoords(TOP_LEFT, x, y);
    setSliceTextureCoords(TOP, x + width, y);
    setSliceTextureCoords(TOP_RIGHT, x + width * 2, y);
    setSliceTextureCoords(LEFT, x, y + height);
    setSliceTextureCoords(MIDDLE, x + width, y + height);
    setSliceTextureCoords(RIGHT, x + width * 2, y + height);
    setSliceTextureCoords(BOTTOM_LEFT, x, y + height * 2);
    setSliceTextureCoords(BOTTOM, x + width, y + height * 2);
    setSliceTextureCoords(BOTTOM_RIGHT, x + width * 2, y + height * 2);

    if (m_state == StatePressed)
    {
        onRelease();
    }
    else if (state == StatePressed)
    {
        onPress();
    }
    m_state = state;
}


void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = &Theme::getTexture();
    target.draw(m_vertices, VERTEX_COUNT, sf::Quads, states);
}


void Box::centerTextHorizontally(sf::Text& text)
{
    sf::Vector2f size = getSize();
    sf::FloatRect textSize = text.getLocalBounds();
    int x = getPosition().x + (size.x - textSize.width) / 2;
    text.setPosition(x, Theme::borderSize + Theme::PADDING);
}


void Box::centerTextVertically(sf::Text& text)
{
    sf::Vector2f size = getSize();
    sf::FloatRect textSize = text.getLocalBounds();
    int y = getPosition().y + (size.y - textSize.width) / 2;
    text.setPosition(Theme::getBoxHeight() - Theme::PADDING, y);
}

}
