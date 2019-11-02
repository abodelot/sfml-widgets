#ifndef GUI_TEXTBOX_HPP
#define GUI_TEXTBOX_HPP

#include "Widget.hpp"
#include "Utils/Box.hpp"

namespace gui
{

/**
 * The TextBox widget is a one-line text editor.
 * It allows the user to enter and edit a single line of plain text.
 */
class TextBox: public Widget
{
public:
    TextBox(float width = 200.f);

    /**
     * Define textbox content
     */
    void setText(const sf::String& string);

    /**
     * Get textbox content
     */
    const sf::String& getText() const;

    /**
     * Define max length of textbox content (default is 256 characters)
     */
    void setMaxLength(size_t maxLength);

    /**
     * Set the cursor position
     */
    void setCursor(size_t index);

    /**
     * Get the cursor position
     */
    size_t getCursor() const;

protected:
    // Callbacks
    void onKeyPressed(const sf::Event::KeyEvent& key) override;
    void onMousePressed(float x, float y) override;
    void onTextEntered(sf::Uint32 unicode) override;
    void onStateChanged(State state) override;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Text    m_text;
    Box         m_box;
    mutable sf::RectangleShape m_cursor;
    mutable sf::Clock  m_cursorTimer;
    size_t             m_cursorPos;
    size_t             m_maxLength;
};

}

#endif // GUI_TEXTBOX_HPP
