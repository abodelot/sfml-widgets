#ifndef GUI_VBOXLAYOUT_HPP
#define GUI_VBOXLAYOUT_HPP

#include "Layout.hpp"

namespace gui
{

/**
 * Vertically stacked layout
 */
class VBoxLayout: public Layout
{
public:
	Widget* add(Widget* widget, int id = -1) override;

private:
	void recomputeGeometry() override;
};

}


#endif // GUI_VBOXLAYOUT_HPP
