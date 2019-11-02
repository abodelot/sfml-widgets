#ifndef GUI_HBOXLAYOUT_HPP
#define GUI_HBOXLAYOUT_HPP

#include "Layout.hpp"

namespace gui
{

/**
 * Horizontally stacked layout
 */
class HBoxLayout: public Layout
{
public:
private:
    void recomputeGeometry() override;
};

}

#endif // GUI_HBOXLAYOUT_HPP
