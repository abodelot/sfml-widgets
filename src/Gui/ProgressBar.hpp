#ifndef GUI_PROGRESS_BAR_HPP
#define GUI_PROGRESS_BAR_HPP

#include "Widget.hpp"
#include "Utils/Box.hpp"
#include "Enums/Enums.hpp"

namespace gui
{

enum LabelPlacement
{
    LabelNone,   // Do no display the label
    LabelOver,   // Display the label over the progress bar
    LabelOutside // Display the label outside the progress bar
};

/**
 * This widget provides a horizontal progress bar.
 * Passive widget: cannot be focused or trigger event
 */
class ProgressBar: public Widget
{
public:
    /**
     * @param length: bar length bar in pixels (Horizontal or Vertical, according to orientation)
     * @param orientation: orientation of the progress bar (Horizontal or Vertical)
     * @param labelPlacement: where to place the label (XXX%)
     */
    ProgressBar(float length = 200.f, Orientation orientation = Horizontal, LabelPlacement labelPlacement = LabelOver);

    /// [0..100]
    void setValue(float value);
    float getValue() const;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    Box m_box;
    Orientation m_orientation;
    sf::Vertex m_bar[4];
    sf::Text m_label;
    LabelPlacement m_labelPlacement;
    float m_value;
};

}

#endif // GUI_PROGRESS_BAR_HPP
