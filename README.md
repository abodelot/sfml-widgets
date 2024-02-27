SFML Widgets
============

A simple GUI module for SFML.

- Spritesheet based: a single image file to customize widget style
- Simple events: set a `std::function<void(void)>` callback on widgets to trigger functions on UI events.
- Layouts: automatically align content without computing positions

![workflow](https://github.com/abodelot/sfml-widgets/actions/workflows/ci.yml/badge.svg)

- Author: Alexandre Bodelot <alexandre.bodelot@gmail.com>
- License: [MIT License](http://opensource.org/licenses/MIT) (See LICENSE file)

## Requirements:
- [Download SFML 2.6.x](https://www.sfml-dev.org/download.php) for your platform
- Latest [CMake Installer](https://cmake.org/download/) - version 3.20 or higher

### Windows:
- Visual Studio 2022 or later (select complete "**Desktop C++ Development**" workload)
- CMake for VS2022 (download using Visual Studio installer).
  
### MacOS
- XCode latest with MacOS SDK.
- Follow [official guide](https://www.sfml-dev.org/tutorials/2.6/start-osx.php) on installing SFML on MacOS
- Extra Apple Developer Tools. After Xcode installs, run this in Terminal:
  ```bash
  sudo xcode-select --install
  ```
- After CMake GUI installs on your Mac, make sure to add its CLI to PATH:
  ```bash
   sudo "/Applications/CMake.app/Contents/bin/cmake-gui" --install
  ```

### Linux Desktop
- Use your package manager (`apt-get` or `yum`) to download SFML dev dependencies listed [in official docs](https://www.sfml-dev.org/tutorials/2.6/compile-with-cmake.php#installing-dependencies)

## Building locally

- On Windows, open this project in Visual Studio 2022 or later, choose "Release" or "Debug" from top toolbar. Then click "Build" > "Build All".
- If using CMake GUI (all platforms), set "Source Folder" to this project root. Then set "Build Folder" to new _relative_ folder `/build` or `/out`. See image below. Then click "Configure", choose **Unix Makefiles**, then click Generate. Finally, open build folder, then run `make all` in Terminal.

 ![cmake_screenshot](doc/cmake_gui.png)
 
- Alternatively, you can use the CMake CLI on your Terminal:

```bash
mkdir build
cd build
cmake . .
cmake --build . --config Release --target all
```


## How to use the library

1. Load resources (font, spritesheet) in static class `gui::Theme`
2. Use `gui::Menu` to create a new sfml-widgets menu. It needs to be connected to your SFML render window, which is given to the constructor.
3. Create widgets, add theme to the menu and define callbacks on them. NOTE: widgets must be dynamically allocated (`new`). The `gui::Menu` destructor will take care of deallocating widgets.

Minimal example:

```cpp
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Gui/Gui.hpp"

int main()
{
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML Widgets", sf::Style::Close);
     
    //Set FPS limit
    //app.setFramerateLimit(60);

    // Declare menu
    gui::Menu menu(app);

    gui::Theme::loadFont("resources/tahoma.ttf");
    gui::Theme::loadTexture("resources/texture-default.png"); 

    // Create some button widget
    gui::Button* button = new gui::Button("My button");

    // Insert button into menu
    menu.add(button);

    // Define a callback
    button->setCallback([] {
        std::cout << "click!" << std::endl;
    });

    // Start the application loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Send events to the menu
            menu.onEvent(event);

            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Optional: clear window with theme background color
        app.clear(gui::Theme::windowBgColor);

        // Render menu
        app.draw(menu);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
```

`demo/demo.cpp` conains a more complex example, featuring all widgets.

![demo_screenshot](doc/demo_screenshot.png)

## Widgets

### `gui::Button`

A simple press button.

![button](doc/button.png)

### `gui::Checkbox`

A button with enabled/disabled state.

![checkbox](doc/checkbox.png)

### `gui::Image`

Displays an SFML texture.

It's a simple wrapper around `sf::Texture`, to display a texture as part of the UI.

### `gui::Label`

A static text element.

It's a simple wrapper around `sf::Text`, to display a text as part of the UI.

### `gui::OptionsBox`

A list of label/value pairs.

![optionsbox](doc/optionsbox.png)

Use templates to define value type. Example: `gui::OptionsBox<sf::Color>`.

Add value with: `optionsBox->addItem("Red", sf::Color::Red)`;

### `gui::ProgressBar`

A simple horizontal or vertical progress bar.

![progress-bar](doc/progress-bar.png)

* `orientation`: `gui::Horizontal` or `gui::Vertical`
* `labelPlacement`: `gui::LabelNone`, or `gui::LabelOver`, or `gui::Outside`

### `gui::Slider`

Provides an horizontal or vertical slider.

![slider](doc/slider.png)

* `orientation`: `gui::Horizontal` or `gui::Vertical`

### `gui::TextBox`

A one-line text editor.

![textbox](doc/textbox.png)

It supports text cursor, and text selection (with mouse or keyboard shortcuts).

## Layouts

Layouts are containers for widgets. They are also widgets themselves, and can be nested!

### `gui::Menu`

The special, unique root layout. It behave like a `VBoxLayout`.

### `gui::HBoxLayout`

Lines up widgets horizontally.

Use `layout->add(widget)` to append a widget on a new line.

### `gui::VBoxLayout`

Lines up widgets vertically.

Use `layout->add(widget)` to append a widget on a new column.

### `gui::FormLayout`

Manages forms of input widgets and their associated labels.

Use `layout->addRow("my label", widget)` to add a new line with label on the left, and widget on the right.

## Theming

To customize the theme, you can:

- Change the theme values (padding, color, font, etc.) defined the static class `gui::Theme`.
- Use a custom spritesheet image.
