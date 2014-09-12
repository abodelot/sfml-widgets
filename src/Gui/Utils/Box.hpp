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
		sf::Vector2f item_size = item.getSize();
		// Center item
		item.setPosition(int(getPosition().x + (size.x - item_size.x) / 2),
	                     int(getPosition().y + (size.y - item_size.y) / 2));
	}

	void centerText(sf::Text& item);


protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void onPress() {};
	virtual void onRelease() {};

	Type m_type;
private:
	enum
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

	void setTextureCoords(int index, float x, float y);

	void setTexturePos(int index, float x, float y, float w, float h);

	//void setBodyColor(const sf::Color& color);

	//void setBorderColor(const sf::Color&, const sf::Color&);

	State m_state;
	static const size_t VERTEX_COUNT = 9 * 4;
	sf::Vertex m_vertices[VERTEX_COUNT];
};


}


#endif // GUI_BOX_HPP
