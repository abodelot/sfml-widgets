#ifndef GUI_SLIDER_HPP
#define GUI_SLIDER_HPP

#include "Widget.hpp"
#include "Utils/Box.hpp"

namespace gui
{

/**
 * This widget provides a vertical or horizontal slider.
 * The slider is the classic widget for controlling a bounded value.
 * The callback is triggered when 'Return' key is pressed.
 */
class Slider: public Widget
{
public:
	enum Type { Horizontal, Vertical };

	Slider(float length = 200, Type type = Horizontal);

	int getQuantum() const;

	void setQuantum(int quantum);

	int getValue() const;

	void setValue(int value);


	// callbacks ---------------------------------------------------------------
	void onKeyPressed(sf::Keyboard::Key key);
	void onMousePressed(float x, float y);
	void onMouseMoved(float x, float y);
	void onMouseReleased(float x, float y);
	void onMouseWheelMoved(int delta);
	void onStateChanged(State state);

private:
	void updateHandlePosition();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Type m_type;
	int  m_quantum;
	int  m_value;
	Box  m_box;
	sf::Vertex m_progression[4];
	Box  m_handle;
};

}

#endif // GUI_SLIDER_HPP
