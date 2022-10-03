SFML Widgets
============

A simple GUI module for SFML.

![workflow](https://github.com/abodelot/sfml-widgets/actions/workflows/ci.yml/badge.svg)

- Author: Alexandre Bodelot <alexandre.bodelot@gmail.com>
- License: [MIT License](http://opensource.org/licenses/MIT) (See LICENSE file)

Run `make` to build the library (`lib/libsfml-widgets.a`) and the demo program.

You can then run the demo: `./sfml-widgets-demo`

## Widgets

* `gui::Button`: a simple press button
* `gui::Checkbox`: a button with enabled/disabled state
* `gui::Image`: displays an SFML texture
* `gui::Label`: a text element
* `gui::OptionsBox`: a list of label/value pairs
* `gui::ProgressBar`: a simple horizontal or vertical progress bar
* `gui::Slider`: provides an horizontal or vertical slider
* `gui::TextBox`: a one-line text editor
* Layouts:
    * `gui::HBoxLayout`: lines up widgets horizontally
    * `gui::VBoxLayout`: lines up widgets vertically
    * `gui::FormLayout`: manages forms of input widgets and their associated labels
