#ifndef GUI_BOX_HPP
#define GUI_BOX_HPP

#include <SFML/Graphics.hpp>
#include "../Widget.hpp"

namespace gui
{

/**
 * Utility class used by widgets for holding visual components
 */
class Box: public sf::Drawable
{
public:
    enum Type
    {
        Input,
        Click
    };

    Box(Type type = Click);

    /**
     * Get box position
     */
    const sf::Vector2f& getPosition() const;

    void setPosition(float x, float y);

    /**
     * Set the box dimensions
     */
    void setSize(float width, float height);

    /**
     * Get box dimensions
     */
    sf::Vector2f getSize() const;

    void press();

    void release();

    /**
     * @return true if point is inside the box limits
     */
    bool containsPoint(float x, float y) const;

    void applyState(State state);

    template <class T>
    void centerItem(T& item)
    {
        sf::Vector2f size = getSize();
        sf::Vector2f itemSize = item.getSize();
        // Center item
        item.setPosition(
            int(getPosition().x + (size.x - itemSize.x) / 2), int(getPosition().y + (size.y - itemSize.y) / 2)
        );
    }

    void centerTextHorizontally(sf::Text& item);

    void centerTextVertically(sf::Text& item);

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    virtual void onPress() {};
    virtual void onRelease() {};

    Type m_type;

private:
    enum Slice
    {
        TOP_LEFT,
        TOP,
        TOP_RIGHT,
        LEFT,
        MIDDLE,
        RIGHT,
        BOTTOM_LEFT,
        BOTTOM,
        BOTTOM_RIGHT
    };

    /**
     * Set the texture coords for one of the 9 slices
     */
    void setSliceTextureCoords(Slice slice, float x, float y);

    /**
     * Set the geometry for one of the 9 slices
     */
    void setSliceGeometry(Slice slice, float x1, float y1, float x2, float y2);

    State m_state;

    // The box is a 9-slices plane, 4 vertices per slice
    static constexpr size_t VERTEX_COUNT = 9 * 4;
    sf::Vertex m_vertices[VERTEX_COUNT];
};

}

#endif // GUI_BOX_HPP
