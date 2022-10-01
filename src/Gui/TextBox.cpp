#include "TextBox.hpp"
#include "Theme.hpp"

#include <SFML/OpenGL.hpp>

#define BLINK_PERIOD 1.f

namespace gui
{

TextBox::TextBox(float width):
    m_box(Box::Input),
    m_cursorPos(0),
    m_maxLength(256),
    m_selectionFirst(0),
    m_selectionLast(0)
{
    m_box.setSize(width, Theme::getBoxHeight());

    int offset = Theme::borderSize + Theme::PADDING;
    m_text.setFont(Theme::getFont());
    m_text.setPosition(offset, offset);
    m_text.setFillColor(Theme::input.textColor);
    m_text.setCharacterSize(Theme::textSize);

    m_placeholder.setFont(Theme::getFont());
    m_placeholder.setPosition(offset, offset);
    m_placeholder.setFillColor(Theme::input.textPlaceholderColor);
    m_placeholder.setCharacterSize(Theme::textSize);

    // Build cursor
    m_cursor.setPosition(offset, offset);
    m_cursor.setSize(sf::Vector2f(1.f, Theme::getLineSpacing()));
    m_cursor.setFillColor(Theme::input.textColor);
    setCursor(0);

    setSize(m_box.getSize());
}


void TextBox::setText(const sf::String& string)
{
    // Trim current text if needed
    if (string.getSize() > m_maxLength)
    {
        m_text.setString(string.substring(0, m_maxLength));
    }
    else
    {
        m_text.setString(string);
    }
    setCursor(getText().getSize());
}


const sf::String& TextBox::getText() const
{
    return m_text.getString();
}


void TextBox::setMaxLength(size_t maxLength)
{
    m_maxLength = maxLength;
    // Trim current text if needed
    if (m_text.getString().getSize() > m_maxLength)
    {
        m_text.setString(m_text.getString().substring(0, m_maxLength));
        setCursor(m_maxLength);
    }
}


void TextBox::setCursor(size_t index)
{
    if (index <= m_text.getString().getSize())
    {
        m_cursorPos = index;
        m_selectionFirst = index;
        m_selectionLast = index;

        float padding = Theme::borderSize + Theme::PADDING;
        m_cursor.setPosition(m_text.findCharacterPos(index).x, padding);
        m_cursorTimer.restart();

        if (m_cursor.getPosition().x > getSize().x - padding)
        {
            // Shift text on left
            float diff = m_cursor.getPosition().x - getSize().x + padding;
            m_text.move(-diff, 0);
            m_cursor.move(-diff, 0);
        }
        else if (m_cursor.getPosition().x < padding)
        {
            // Shift text on right
            float diff = padding - m_cursor.getPosition().x;
            m_text.move(diff, 0);
            m_cursor.move(diff, 0);
        }

        float textWidth = m_text.getLocalBounds().width;
        if (m_text.getPosition().x < padding && m_text.getPosition().x + textWidth < getSize().x - padding)
        {
            float diff = (getSize().x - padding) - (m_text.getPosition().x + textWidth);
            m_text.move(diff, 0);
            m_cursor.move(diff, 0);
            // If text is smaller than the textbox, force align on left
            if (textWidth < (getSize().x - padding * 2))
            {
                diff = padding - m_text.getPosition().x;
                m_text.move(diff, 0);
                m_cursor.move(diff, 0);
            }
        }
    }
}


size_t TextBox::getCursor() const
{
    return m_cursorPos;
}


void TextBox::onKeyPressed(const sf::Event::KeyEvent& key)
{
    switch (key.code)
    {
    case sf::Keyboard::Left:
        if (key.shift)
        {
            if (m_cursorPos == m_selectionLast)
            {
                // Extend selection to left
                if (m_selectionFirst > 0)
                    setSelectedText(m_selectionFirst - 1, m_selectionLast);
            }
            else
            {
                // Shrink selection to right
                setSelectedText(m_selectionFirst, m_selectionLast - 1);
            }
        }
        else if (m_selectedText.isEmpty())
        {
            // Move cursor to the left
            setCursor(m_cursorPos - 1);
        }
        else
        {
            // Clear selection, move cursor to the left
            setCursor(m_selectionFirst);
            clearSelectedText();
        }
        break;

    case sf::Keyboard::Right:
        if (key.shift)
        {
            if (m_cursorPos == m_selectionFirst)
            {
                // Extend selection to right
                if (m_selectionLast < m_text.getString().getSize())
                    setSelectedText(m_selectionFirst, m_selectionLast + 1);
            }
            else
            {
                // Shrink selection to left
                setSelectedText(m_selectionFirst + 1, m_selectionLast);
            }
        }
        else if (m_selectedText.isEmpty())
        {
            // Move cursor to the right
            setCursor(m_cursorPos + 1);
        }
        else
        {
            // Clear selection, move cursor to the right
            setCursor(m_selectionLast);
            clearSelectedText();
        }
        break;

    case sf::Keyboard::BackSpace:
        if (!m_selectedText.isEmpty())
        {
            deleteSelectedText();
            break;
        }
        // Erase character before cursor
        if (m_cursorPos > 0)
        {
            sf::String string = m_text.getString();
            string.erase(m_cursorPos - 1);
            m_text.setString(string);

            setCursor(m_cursorPos - 1);
        }
        break;

    case sf::Keyboard::Delete:
        if (!m_selectedText.isEmpty())
        {
            deleteSelectedText();
            break;
        }
        // Erase character after cursor
        if (m_cursorPos < m_text.getString().getSize())
        {
            sf::String string = m_text.getString();
            string.erase(m_cursorPos);
            m_text.setString(string);

            setCursor(m_cursorPos);
        }
        break;

    case sf::Keyboard::Home:
        if (key.shift)
        {
            // Shift+Home: select from start to cursor
            setSelectedText(0, m_cursorPos);
        }
        else
        {
            setCursor(0);
        }
        break;

    case sf::Keyboard::End:
        if (key.shift)
        {
            // Shift+End: select from cursor to end
            setSelectedText(m_cursorPos, m_text.getString().getSize());
        }
        else
        {
            setCursor(m_text.getString().getSize());
        }
        break;

    case sf::Keyboard::Return:
        triggerCallback();
        break;

    // Ctrl+A: select all
    case sf::Keyboard::A:
        if (key.control)
        {
            setSelectedText(0, m_text.getString().getSize());
        }
        break;

    // Ctrl+V: paste clipboard
    case sf::Keyboard::V:
        if (key.control)
        {
            // Delete selected text and write clipboard string over it.
            deleteSelectedText();
            sf::String string = m_text.getString();
            sf::String clipboardString = sf::Clipboard::getString();
            // Trim clipboard content if needed
            if ((string.getSize() + clipboardString.getSize()) > m_maxLength)
            {
                clipboardString = clipboardString.substring(0, m_maxLength - string.getSize());
            }
            // Insert string at cursor position
            string.insert(m_cursorPos, clipboardString);
            m_text.setString(string);
            setCursor(m_cursorPos + clipboardString.getSize());
        }
        break;

    // Ctrl+C: copy selected text to clipboard
    case sf::Keyboard::C:
        if (key.control)
        {
            if (!m_selectedText.isEmpty())
            {
                sf::Clipboard::setString(m_selectedText);
            }
        }
        break;

    // Ctrl+X: cut selected text to clipboard
    case sf::Keyboard::X:
        if (key.control)
        {
            if (!m_selectedText.isEmpty())
            {
                sf::Clipboard::setString(m_selectedText);
                deleteSelectedText();
            }
        }
        break;

    default:
        break;
    }
}


void TextBox::onMouseEnter()
{
    setMouseCursor(sf::Cursor::Text);
}


void TextBox::onMouseLeave()
{
    setMouseCursor(sf::Cursor::Arrow);
}


void TextBox::onMousePressed(float x, float)
{
    for (int i = m_text.getString().getSize(); i >= 0; --i)
    {
        // Place cursor after the character under the mouse
        sf::Vector2f glyphPos = m_text.findCharacterPos(i);
        if (glyphPos.x <= x)
        {
            setCursor(i);
            break;
        }
    }
}


void TextBox::onMouseReleased(float x, float)
{
    for (int i = m_text.getString().getSize(); i >= 0; --i)
    {
        // Place cursor after the character under the mouse
        sf::Vector2f glyphPos = m_text.findCharacterPos(i);
        if (glyphPos.x <= x)
        {
            setSelectedText(m_cursorPos, i);
            break;
        }
    }
}


void TextBox::onMouseMoved(float x, float)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        for (int i = m_text.getString().getSize(); i >= 0; --i)
        {
            // Place cursor after the character under the mouse
            sf::Vector2f glyphPos = m_text.findCharacterPos(i);
            if (glyphPos.x <= x)
            {
                setSelectedText(m_cursorPos, i);
                break;
            }
        }
    }
}


void TextBox::onTextEntered(sf::Uint32 unicode)
{
    if (unicode > 30 && (unicode < 127 || unicode > 159))
    {
        // Delete selected text when a new input is received
        deleteSelectedText();
        sf::String string = m_text.getString();
        if (string.getSize() < m_maxLength)
        {
            // Insert character in string at cursor position
            string.insert(m_cursorPos, unicode);
            m_text.setString(string);
            setCursor(m_cursorPos + 1);
        }
    }
}


void TextBox::onStateChanged(State state)
{
    m_box.applyState(state);

    // Discard selection when focus is lost
    if (state != State::StateFocused)
    {
        clearSelectedText();
    }
}


void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_box, states);

    // Crop the text with GL Scissor
    glEnable(GL_SCISSOR_TEST);

    sf::Vector2f pos = getAbsolutePosition();
    glScissor(pos.x + Theme::borderSize, target.getSize().y - (pos.y + getSize().y), getSize().x, getSize().y);

    if (m_text.getString().isEmpty())
    {
        target.draw(m_placeholder, states);
    }
    else
    {
        // Draw selection indicator
        if (!m_selectedText.isEmpty())
        {
            sf::RectangleShape selRect;
            const sf::Vector2f& startPos = m_text.findCharacterPos(m_selectionFirst);
            selRect.setPosition(startPos);
            selRect.setSize({m_text.findCharacterPos(m_selectionLast).x - startPos.x, m_cursor.getSize().y});
            selRect.setFillColor(Theme::input.textSelectionColor);
            target.draw(selRect, states);
        }
        target.draw(m_text, states);
    }

    glDisable(GL_SCISSOR_TEST);

    // Show cursor if focused and no selection
    if (isFocused() && m_selectedText.isEmpty())
    {
        // Make it blink
        float timer = m_cursorTimer.getElapsedTime().asSeconds();
        if (timer >= BLINK_PERIOD)
            m_cursorTimer.restart();

        // Updating in the drawing method, deal with it
        sf::Color color = Theme::input.textColor;
        color.a = 255 - (255 * timer / BLINK_PERIOD);
        m_cursor.setFillColor(color);

        target.draw(m_cursor, states);
    }
}


void TextBox::setSelectedText(size_t from, size_t to)
{
    if (from != to)
    {
        size_t selectionLast = std::max(from, to);
        size_t selectionFirst = std::min(from, to);
        if (selectionFirst != m_selectionFirst || selectionLast != m_selectionLast)
        {
            m_selectionFirst = selectionFirst;
            m_selectionLast = selectionLast;
            m_selectedText = m_text.getString().substring(m_selectionFirst, m_selectionLast - m_selectionFirst);
        }
    }
    else
    {
        clearSelectedText();
    }
}


void TextBox::clearSelectedText()
{
    m_selectionFirst = m_selectionLast = m_cursorPos;
    m_selectedText.clear();
}


const sf::String& TextBox::getSelectedText() const
{
    return m_selectedText;
}


void TextBox::deleteSelectedText()
{
    // Delete if any selected text
    if (!m_selectedText.isEmpty())
    {
        sf::String str = m_text.getString();
        str.erase(m_selectionFirst, m_selectionLast - m_selectionFirst);
        setCursor(m_selectionFirst);
        clearSelectedText();
        m_text.setString(str);
    }
}


void TextBox::setPlaceholder(const sf::String& placeholder)
{
    m_placeholder.setString(placeholder);
}


const sf::String& TextBox::getPlaceholder() const
{
    return m_placeholder.getString();
}

}
