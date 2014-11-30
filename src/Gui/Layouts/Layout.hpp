#ifndef GUI_LAYOUT_HPP
#define GUI_LAYOUT_HPP

#include "../Widget.hpp"

namespace gui
{

class Widget;
class Label;
class Button;
class FormLayout;
class HBoxLayout;
class VBoxLayout;

/**
 * Base class for layouts. Layouts are special widgets which act as containers
 * See FormLayout, HBoxLayout and VBoxLayout
 */
class Layout: public Widget
{
public:
	Layout();
	~Layout();

	/**
	 * Add a new widget in the container
	 * The container will take care of widget deallocation
	 * @return added widget
	 */
	virtual Widget* add(Widget* widget, int id = -1) = 0;

	/// Helpers
	Button*     addButton(const sf::String& string, int id = -1);
	Label*      addLabel(const sf::String& string);
	FormLayout* addFormLayout();
	HBoxLayout* addHBoxLayout();
	VBoxLayout* addVBoxLayout();

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Callbacks ---------------------------------------------------------------
	void onStateChanged(State state) override;
	void onMouseMoved(float x, float y) override;
	void onMousePressed(float x, float y) override;
	void onMouseReleased(float x, float y) override;
	void onMouseWheelMoved(int delta) override;
	void onKeyPressed(sf::Keyboard::Key key) override;
	void onKeyReleased(sf::Keyboard::Key key) override;
	void onTextEntered(sf::Uint32 unicode) override;

	Layout* toLayout() override { return this; } // hack?
	bool focusNextWidget();
	bool focusPreviousWidget();

	/**
	 * Append a new widget in the container
	 */
	Widget* push(Widget* widget);

	Widget* getFirstWidget();

private:
	/**
	 * Give the focus to a widget, if applicable
	 * @param state: new state of the widget if it took focus
	 * @return true if widget took the focus, otherwise false
	 */
	bool focusWidget(Widget* widget, State state = StateFocused);

	Widget*   m_first;
	Widget*   m_last;
	Widget*   m_hover;
	Widget*   m_focus;
};

}

#endif // GUI_LAYOUT_HPP
