#include "Gui/Menu.hpp"
#include "Gui/Theme.hpp"
#include "Gui/Gui.hpp"


sf::Color mkcolor(const std::string& hexcolor)
{
    sf::Color color = sf::Color::Black;
    if (hexcolor.size() == 7) // #ffffff
    {
        color.r = strtoul(hexcolor.substr(1, 2).c_str(), NULL, 16);
        color.g = strtoul(hexcolor.substr(3, 2).c_str(), NULL, 16);
        color.b = strtoul(hexcolor.substr(5, 2).c_str(), NULL, 16);
    }
    else if (hexcolor.size() == 4) // #fff
    {
        color.r = strtoul(hexcolor.substr(1, 1).c_str(), NULL, 16) * 17;
        color.g = strtoul(hexcolor.substr(2, 1).c_str(), NULL, 16) * 17;
        color.b = strtoul(hexcolor.substr(3, 1).c_str(), NULL, 16) * 17;
    }
    return color;
}


int main()
{
    enum Callback
    {
        C_TEXT,
        C_COLOR,
        C_ROTATION,
        C_BOLD,
        C_UNDERLINED,
        C_SCALE,
        C_NEW_BUTTON,
        C_VSLIDER,
        C_QUIT
    };

    // Create the main window
    sf::RenderWindow app(sf::VideoMode(640, 480), "SFML Widgets");

    gui::Menu menu(app);
    menu.setPosition(10, 10);

    gui::Theme::loadFont("resources/tahoma.ttf");
    gui::Theme::loadTexture("resources/texture.png");
    gui::Theme::textSize = 11;
    gui::Theme::click.textColor      = mkcolor("#191B18");
    gui::Theme::click.textColorHover = mkcolor("#191B18");
    gui::Theme::click.textColorFocus = mkcolor("#000");
    gui::Theme::input.textColor = mkcolor("#000");
    gui::Theme::input.textColorHover = mkcolor("#000");
    gui::Theme::input.textColorFocus = mkcolor("#000");
    gui::Theme::PADDING = 2.f;
    gui::Theme::windowBgColor = mkcolor("#dddbde");

    gui::HBoxLayout* hbox = menu.addHBoxLayout();
    gui::FormLayout* form = hbox->addFormLayout();

    // Textbox
    gui::TextBox* textbox = new gui::TextBox();
    textbox->setText("Hello, World!");
    form->addRow("Text", textbox, C_TEXT);

    // Slider for rotation
    gui::Slider* sliderRotation = new gui::Slider();
    sliderRotation->setQuantum(1);
    form->addRow("Rotation", sliderRotation, C_ROTATION);

    // Slider for scale
    gui::Slider* sliderScale = new gui::Slider();
    form->addRow("Scale", sliderScale, C_SCALE);

    // OptionsBox for color
    gui::OptionsBox<sf::Color>* opt = new gui::OptionsBox<sf::Color>();
    opt->addItem("Red", sf::Color::Red);
    opt->addItem("Blue", sf::Color::Blue);
    opt->addItem("Green", sf::Color::Green);
    opt->addItem("Yellow", sf::Color::Yellow);
    opt->addItem("White", sf::Color::White);
    form->addRow("Color", opt, C_COLOR);

    // Checbkox
    gui::CheckBox* checkboxBold = new gui::CheckBox();
    form->addRow("Bold text", checkboxBold, C_BOLD);

    gui::CheckBox* checkboxUnderlined = new gui::CheckBox();
    form->addRow("Underlined text", checkboxUnderlined, C_UNDERLINED);

    // Progress bar
    gui::ProgressBar* pbar0 = new gui::ProgressBar();
    form->addRow("Progress bar", pbar0);
    form->addRow("Default button", new gui::Button("button"));

    // Custom button
    sf::Texture imgbutton;
    imgbutton.loadFromFile("resources/themed-button.png");

    gui::SpriteButton* customButton = new gui::SpriteButton(imgbutton, "Play game");

    customButton->setTextSize(18);
    form->addRow("Custom button", customButton);

    gui::VBoxLayout* vbox = hbox->addVBoxLayout();
    vbox->addLabel("This pannel is on the left");

    // Textbox
    gui::HBoxLayout* hbox2 = vbox->addHBoxLayout();
    gui::TextBox* textbox2 = new gui::TextBox(100);
    textbox2->setText("Button name");
    hbox2->add(textbox2, C_NEW_BUTTON);
    hbox2->addButton("Create button", C_NEW_BUTTON);

    // Small progress bar
    gui::HBoxLayout* hbox3 = vbox->addHBoxLayout();
    hbox3->addLabel("Small progress bar");
    gui::ProgressBar* pbar = new gui::ProgressBar(40);
    hbox3->add(pbar);

    gui::Slider* vslider = new gui::Slider(100, gui::Slider::Vertical);
    hbox->add(vslider, C_VSLIDER);

    menu.addButton("Quit", C_QUIT);

    sf::Texture texture;
    texture.loadFromFile("resources/sfml.png");

    sf::Sprite sprite(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setPosition(300, 360);

    sf::Text text(textbox->getText(), gui::Theme::getFont());
    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
    text.setPosition(320, 360);

    // Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            int id = menu.onEvent(event);
            switch (id)
            {
                case C_TEXT:
                    text.setString(textbox->getText());
                    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
                    break;
                case C_COLOR:
                    text.setFillColor(opt->getSelectedValue());
                    break;
                case C_ROTATION:
                    text.setRotation(sliderRotation->getValue() * 360 / 100.f);
                    pbar0->setValue(sliderRotation->getValue());
                    break;
                case C_UNDERLINED:
                {
                    int style = text.getStyle();
                    if (checkboxUnderlined->isChecked())
                        style |= sf::Text::Underlined;
                    else
                        style &= ~sf::Text::Underlined;
                    text.setStyle(style);
                    break;
                }
                case C_BOLD:
                {
                    int style = text.getStyle();
                    if (checkboxBold->isChecked())
                        style |= sf::Text::Bold;
                    else
                        style &= ~sf::Text::Bold;
                    text.setStyle(style);
                    break;
                }
                case C_SCALE:
                {
                    float scale = 1 + sliderScale->getValue() * 2 / 100.f;
                    text.setScale(scale, scale);
                    break;
                }
                case C_QUIT:
                    app.close();
                    break;
                case C_VSLIDER:
                    pbar->setValue(vslider->getValue());
                    break;
                case C_NEW_BUTTON:
                    vbox->addButton(textbox2->getText());
                    break;
            }
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Clear screen
        app.clear(gui::Theme::windowBgColor);
        app.draw(menu);
        app.draw(text);
        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
