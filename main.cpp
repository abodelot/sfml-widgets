#include <iostream>
#include <SFML/Graphics.hpp>
#include "Gui/Gui.hpp"

int main()
{
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML Widgets", sf::Style::Close);

    // Declare menu
    gui::Menu menu(app);

    gui::Theme::loadFont("demo/tahoma.ttf");
    gui::Theme::loadTexture("demo/texture-default.png");

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

    return 0;
}
