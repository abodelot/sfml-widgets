#ifndef GUI_BUTTON_HPP
#define GUI_BUTTON_HPP

#include "Widget.hpp"
#include "Utils/ItemBox.hpp"

namespace gui
{

/**
 * The Button widget is a simple press button.
 * The callback is triggered when the button is clicked/activated.
 */
class Button: public Widget
{
public:
    Button(const sf::String& string);

    /**
     * Set the displayed button label
     */
    void setString(const sf::String& string);

    const sf::String& getString() const;

protected:
    // Callbacks
    void onStateChanged(State state) override;
    void onMouseMoved(float x, float y) override;
    void onMousePressed(float x, float y) override;
    void onMouseReleased(float x, float y) override;
    void onKeyPressed(const sf::Event::KeyEvent& key) override;
    void onKeyReleased(const sf::Event::KeyEvent& key) override;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    ItemBox<sf::Text> m_box;
};

}

#endif // GUI_BUTTON_HPP
