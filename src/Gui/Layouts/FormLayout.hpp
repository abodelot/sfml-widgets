#ifndef GUI_FORMLAYOUT_HPP
#define GUI_FORMLAYOUT_HPP

#include "Layout.hpp"

namespace gui
{

/**
 * Horizontally stacked layout with a label before each widget
 */
class FormLayout: public Layout
{
public:
    FormLayout();

    /**
     * Add a new label/widget row in the form
     * @param label: label displayed before the widget
     * @param widget: widget to be added
     */
    Widget* addRow(const sf::String& label, Widget* widget);

private:
    void recomputeGeometry() override;

    float m_labelWidth;
};

}

#endif // GUI_FORMLAYOUT_HPP
