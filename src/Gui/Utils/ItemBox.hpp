#ifndef GUI_ITEMBOX_HPP
#define GUI_ITEMBOX_HPP

#include "Box.hpp"

namespace gui
{

/**
 * Utility class used by widgets for holding visual components
 */
template <class T>
class ItemBox: public Box
{
public:
	ItemBox(Box::Type type = Box::Click);
	ItemBox(const T& item, Box::Type type = Box::Click);

	void applyState(State state);

	inline T& item() { return m_item;} //hack
	inline const T& item() const { return m_item;}

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void onPress() override;
	void onRelease() override;

	T    m_item;
};

}

#include "ItemBox.inl"

#endif // GUI_ITEMBOX_HPP
