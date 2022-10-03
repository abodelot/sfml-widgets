#ifndef GUI_SLIDER_HPP
#define GUI_SLIDER_HPP

#include "Widget.hpp"
#include "Utils/Box.hpp"
#include "Enums/Enums.hpp"

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
    Slider(float length = 200, Orientation orientation = Horizontal);

    int getStep() const;

    /**
     * Define the amount of units to change the slider when adjusting by drag and drop
     */
    void setStep(int step);

    int getValue() const;

    void setValue(int value);

protected:
    // Callbacks
    void onKeyPressed(const sf::Event::KeyEvent& key) override;
    void onMousePressed(float x, float y) override;
    void onMouseMoved(float x, float y) override;
    void onMouseReleased(float x, float y) override;
    void onMouseWheelMoved(int delta) override;
    void onStateChanged(State state) override;

private:
    void updateHandlePosition();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    Orientation m_orientation;
    int m_step;
    int m_value;
    Box m_box;
    sf::Vertex m_progression[4];
    Box m_handle;
};

}

#endif // GUI_SLIDER_HPP
