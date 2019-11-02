#ifndef GUI_PROGRESS_BAR_HPP
#define GUI_PROGRESS_BAR_HPP

#include "Widget.hpp"
#include "Utils/Box.hpp"

namespace gui
{

/**
 * This widget provides a horizontal progress bar.
 * Passive widget: cannot be focused or trigger event
 */
class ProgressBar: public Widget
{
public:
    ProgressBar(float width = 200.f);

    /// [0..100]
    void setValue(float value);
    float getValue() const;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    Box        m_box;
    sf::Vertex m_bar[4];
    sf::Text   m_text;
    float      m_value;
};

}

#endif // GUI_PROGRESS_BAR_HPP
