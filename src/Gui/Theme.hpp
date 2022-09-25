#ifndef GUI_THEME_HPP
#define GUI_THEME_HPP

#include <map>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Font.hpp>

#include "Widget.hpp"
#include "Utils/Box.hpp"

namespace gui
{

class Theme
{
public:
    /**
     * Load the GUI global font
     */
    static bool loadFont(const std::string& path);
    static const sf::Font& getFont();

    /**
     * Load the GUI spritesheet
     */
    static bool loadTexture(const std::string& path);
    static const sf::Texture& getTexture();

    static const sf::IntRect& getTextureRect(Box::Type type, State state);

    static const sf::IntRect& getCrossTextureRect();

    static const sf::IntRect& getArrowTextureRect();

    static const sf::IntRect& getProgressBarTextureRect();

    /**
     * Widget height based on text size
     */
    static float getBoxHeight();

    /**
     * Height of a line of text
     */
    static int getLineSpacing();

    static size_t textSize;
    struct Style
    {
        sf::Color textColor;
        sf::Color textColorHover;
        sf::Color textColorFocus;
        sf::Color textSelectionColor;
        sf::Color textPlaceholderColor;
    };

    static Style click;
    static Style input;

    static sf::Color windowBgColor;
    static int borderSize;
    static int minWidgetWidth;

    static float PADDING; // Spacing inside widget
    static float MARGIN;  // Spacing between widgets
    static sf::Keyboard::Key previousWidgetKey;
    static sf::Keyboard::Key nextWidgetKey;

    // Auto-initialized to default cursor
    static sf::Cursor& cursor;

private:
    enum TextureID
    {
        BOX_DEFAULT,
        BOX_HOVERED,
        BOX_PRESSED,
        BOX_FOCUSED,
        BOX_INPUT_DEFAULT,
        BOX_INPUT_FOCUSED,
        CROSS,
        ARROW,
        PROGRESS_BAR,
        _TEXTURE_ID_COUNT
    };

    static sf::Font m_font;
    static sf::Texture m_texture;
    static sf::IntRect m_subrects[_TEXTURE_ID_COUNT];
};

}

#endif // GUI_THEME_HPP
