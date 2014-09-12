#ifndef GUI_CHECKBOX_HPP
#define GUI_CHECKBOX_HPP

#include "Widget.hpp"
#include "Utils/Box.hpp"
#include "Utils/Cross.hpp"

namespace gui
{

/**
 * The CheckBox is a widget for enabling/disabling an option.
 * The callback is triggered when the checkbox is checked or unchecked.
 */
class CheckBox: public Widget
{
public:
	CheckBox(bool checked = false);

	bool isChecked() const;

	void check(bool checked);

	// callbacks ---------------------------------------------------------------

	void onStateChanged(State state);
	void onMouseReleased(float x, float y);
	void onKeyPressed(sf::Keyboard::Key key);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Box   m_box;
	Cross m_cross;
	bool  m_checked;
};

}

#endif // GUI_CHECKBOX_HPP
