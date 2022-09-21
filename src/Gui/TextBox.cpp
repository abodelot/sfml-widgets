#include "TextBox.hpp"
#include "Theme.hpp"

#include <SFML/OpenGL.hpp>

#define BLINK_PERIOD 1.f

namespace gui
{

TextBox::TextBox(float width):
    m_box(Box::Input),
    m_cursorPos(0),
    m_maxLength(256)
{
    m_box.setSize(width, Theme::getBoxHeight());

    int offset = Theme::borderSize + Theme::PADDING;
    m_text.setFont(Theme::getFont());
    m_text.setPosition(offset, offset);
    m_text.setFillColor(Theme::input.textColor);
    m_text.setCharacterSize(Theme::textSize);

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

        float text_width = m_text.getLocalBounds().width;
        if (m_text.getPosition().x < padding
            && m_text.getPosition().x + text_width < getSize().x - padding)
        {
            float diff = (getSize().x - padding) - (m_text.getPosition().x + text_width);
            m_text.move(diff, 0);
            m_cursor.move(diff, 0);
            // If text is smaller than the textbox, force align on left
            if (text_width < (getSize().x - padding * 2))
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
        setCursor(m_cursorPos - 1);
        break;

    case sf::Keyboard::Right:
        setCursor(m_cursorPos + 1);
        break;

    case sf::Keyboard::BackSpace:
        if(!m_selectedText.isEmpty())
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
        if(!m_selectedText.isEmpty())
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
        setCursor(0);
        break;

    case sf::Keyboard::End:
        setCursor(m_text.getString().getSize());
        break;

    case sf::Keyboard::Return:
        triggerCallback();
        break;

    case sf::Keyboard::A:
        if(key.control)
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

    case sf::Keyboard::C:
        if(key.control)
        {
            if(!m_selectedText.isEmpty())
            {
                sf::Clipboard::setString(m_selectedText);
            }
        }
        break;

    case sf::Keyboard::X:
        if(key.control)
        {
            if(!m_selectedText.isEmpty())
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


void TextBox::onMousePressed(float x, float)
{
    for (int i = m_text.getString().getSize(); i >= 0; --i)
    {
        // Place cursor after the character under the mouse
        sf::Vector2f glyph_pos = m_text.findCharacterPos(i);
        if (glyph_pos.x <= x)
        {
            setCursor(i);
            break;
        }
    }
}


void TextBox::onMouseReleased(float x, float y)
{
    for (int i = m_text.getString().getSize(); i >= 0; --i)
    {
        // Place cursor after the character under the mouse
        sf::Vector2f glyph_pos = m_text.findCharacterPos(i);
        if (glyph_pos.x <= x)
        {
            setSelectedText(m_cursorPos, i);
            setCursor(i);
            break;
        }
    }
}


void TextBox::onMouseMoved(float x, float y)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        for (int i = m_text.getString().getSize(); i >= 0; --i)
        {
            // Place cursor after the character under the mouse
            sf::Vector2f glyph_pos = m_text.findCharacterPos(i);
            if (glyph_pos.x <= x)
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
    if(state != State::StateFocused)
    {
        setSelectedText(0,0);
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

    // Draw selection indicator
    if(!m_selectedText.isEmpty())
    {
        sf::RectangleShape selRect;
        selRect.setPosition(m_text.findCharacterPos(m_selectionFirst));
        selRect.setSize({m_text.findCharacterPos(m_selectionLast).x - m_text.findCharacterPos(m_selectionFirst).x, m_cursor.getSize().y});
        selRect.setFillColor(Theme::input.textSelectionColor);
        target.draw(selRect, states);
    }

    target.draw(m_text, states);

    glDisable(GL_SCISSOR_TEST);

    // Show cursor if focused
    if (isFocused())
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
    if(from != to)
    {
        m_selectionLast = std::max(from, to);
        m_selectionFirst = std::min(from, to);
        m_selectedText = m_text.getString().substring(m_selectionFirst, m_selectionLast - m_selectionFirst);
    }
    else
    {
        m_selectionFirst = m_selectionLast = 0;
        m_selectedText.clear();
    }
}

const sf::String& TextBox::getSelectedText() const
{
    return m_selectedText;
}

void TextBox::deleteSelectedText()
{
    // Delete if any selected text
    if(!m_selectedText.isEmpty())
    {
        sf::String str = m_text.getString();
        str.erase(m_selectionFirst, m_selectionLast - m_selectionFirst);
        setCursor(m_selectionFirst);
        setSelectedText(0,0);
        m_text.setString(str);
    }
}


}
