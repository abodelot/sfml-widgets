#include "Gui/Theme.hpp"
#include "Gui/Gui.hpp"
#include <SFML/Graphics.hpp>


sf::Color hex2color(const std::string& hexcolor)
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

struct Theme
{
    sf::Color backgroundColor;
    std::string texturePath;
};

int main()
{
    Theme defaultTheme = {
        hex2color("#dddbde"),
        "demo/texture-default.png"
    };

    Theme win98Theme = {
        hex2color("#d4d0c8"),
        "demo/texture-win98.png"
    };

    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML Widgets", sf::Style::Close);
    app.setFramerateLimit(60);

    gui::Menu menu(app);
    menu.setPosition(10, 10);

    gui::Theme::loadFont("demo/tahoma.ttf");
    gui::Theme::loadTexture(defaultTheme.texturePath);
    gui::Theme::textSize = 11;
    gui::Theme::click.textColor      = hex2color("#191B18");
    gui::Theme::click.textColorHover = hex2color("#191B18");
    gui::Theme::click.textColorFocus = hex2color("#000");
    gui::Theme::input.textColor = hex2color("#000");
    gui::Theme::input.textColorHover = hex2color("#000");
    gui::Theme::input.textColorFocus = hex2color("#000");
    gui::Theme::input.textSelectionColor = hex2color("#8791AD");
    gui::Theme::input.textPlaceholderColor = hex2color("#8791AD");
    gui::Theme::PADDING = 2.f;
    gui::Theme::windowBgColor = defaultTheme.backgroundColor;

    gui::HBoxLayout* hbox = menu.addHBoxLayout();
    gui::FormLayout* form = hbox->addFormLayout();

    sf::Text text("Hello world!", gui::Theme::getFont());
    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
    text.setPosition(480, 240);

    // Textbox
    gui::TextBox* textbox = new gui::TextBox();
    textbox->setText("Hello world!");
    textbox->setCallback([&]() {
        text.setString(textbox->getText());
        text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
    });
    textbox->setPlaceholder("Type something!");
    form->addRow("Text", textbox);

    gui::TextBox* textbox2 = new gui::TextBox();
    textbox2->setText("Hello world!");
    textbox2->setMaxLength(5);
    form->addRow("Text with limit (5)", textbox2);

    // Slider + ProgressBar for rotation
    gui::Slider* sliderRotation = new gui::Slider();
    gui::ProgressBar* pbarRotation1 = new gui::ProgressBar(200.f, gui::Horizontal, gui::LabelNone);
    gui::ProgressBar* pbarRotation2 = new gui::ProgressBar(200.f, gui::Horizontal, gui::LabelOver);
    gui::ProgressBar* pbarRotation3 = new gui::ProgressBar(200.f, gui::Horizontal, gui::LabelOutside);

    sliderRotation->setStep(1);
    sliderRotation->setCallback([&]() {
        text.setRotation(sliderRotation->getValue() * 360 / 100.f);
        pbarRotation1->setValue(sliderRotation->getValue());
        pbarRotation2->setValue(sliderRotation->getValue());
        pbarRotation3->setValue(sliderRotation->getValue());
    });
    form->addRow("Rotation", sliderRotation);

    // Slider + ProgressBar for scale
    gui::Slider* sliderScale = new gui::Slider();
    gui::ProgressBar* pbarScale1 = new gui::ProgressBar(100, gui::Vertical, gui::LabelNone);
    gui::ProgressBar* pbarScale2 = new gui::ProgressBar(100, gui::Vertical, gui::LabelOver);
    gui::ProgressBar* pbarScale3 = new gui::ProgressBar(100, gui::Vertical, gui::LabelOutside);
    sliderScale->setCallback([&]() {
        float scale = 1 + sliderScale->getValue() * 2 / 100.f;
        text.setScale(scale, scale);
        pbarScale1->setValue(sliderScale->getValue());
        pbarScale2->setValue(sliderScale->getValue());
        pbarScale3->setValue(sliderScale->getValue());
    });
    form->addRow("Scale", sliderScale);

    // OptionsBox for color
    gui::OptionsBox<sf::Color>* opt = new gui::OptionsBox<sf::Color>();
    opt->addItem("Red", sf::Color::Red);
    opt->addItem("Blue", sf::Color::Blue);
    opt->addItem("Green", sf::Color::Green);
    opt->addItem("Yellow", sf::Color::Yellow);
    opt->addItem("White", sf::Color::White);
    opt->setCallback([&]() {
        text.setFillColor(opt->getSelectedValue());
    });
    form->addRow("Color", opt);

    // Checbkox
    gui::CheckBox* checkboxBold = new gui::CheckBox();
    checkboxBold->setCallback([&]() {
        int style = text.getStyle();
        if (checkboxBold->isChecked())
            style |= sf::Text::Bold;
        else
            style &= ~sf::Text::Bold;
        text.setStyle(style);
    });
    form->addRow("Bold text", checkboxBold);

    gui::CheckBox* checkboxUnderlined = new gui::CheckBox();
    checkboxUnderlined->setCallback([&]() {
        int style = text.getStyle();
        if (checkboxUnderlined->isChecked())
            style |= sf::Text::Underlined;
        else
            style &= ~sf::Text::Underlined;
        text.setStyle(style);
    });
    form->addRow("Underlined text", checkboxUnderlined);

    // Progress bar
    form->addRow("Progress bar (label = None)", pbarRotation1);
    form->addRow("Progress bar (label = Over)", pbarRotation2);
    form->addRow("Progress bar (label = Outside)", pbarRotation3);

    // Vertical progress bars
    gui::Layout* layoutForVerticalProgressBars = new gui::HBoxLayout();
    layoutForVerticalProgressBars->add(pbarScale1);
    layoutForVerticalProgressBars->add(pbarScale2);
    layoutForVerticalProgressBars->add(pbarScale3);
    form->addRow("Vertical progress bars", layoutForVerticalProgressBars);

    form->addRow("Default button", new gui::Button("button"));

    // Custom button
    sf::Texture imgbutton;
    imgbutton.loadFromFile("demo/themed-button.png");

    gui::SpriteButton* customButton = new gui::SpriteButton(imgbutton, "Play");
    customButton->setTextSize(20);
    form->addRow("Custom button", customButton);

    gui::VBoxLayout* vbox = hbox->addVBoxLayout();
    vbox->addLabel("This pannel is on the left");

    gui::OptionsBox<Theme>* themeBox = new gui::OptionsBox<Theme>();
    themeBox->addItem("Windows 98", win98Theme);
    themeBox->addItem("Default", defaultTheme);
    themeBox->setCallback([&]() {
        const Theme& theme = themeBox->getSelectedValue();
        gui::Theme::loadTexture(theme.texturePath);
        gui::Theme::windowBgColor = theme.backgroundColor;
    });
    vbox->add(themeBox);

    // Textbox
    gui::HBoxLayout* hbox2 = vbox->addHBoxLayout();
    gui::TextBox* textbox3 = new gui::TextBox(100);
    textbox3->setText("My Button");
    textbox3->setPlaceholder("Button label");
    hbox2->add(textbox3);
    hbox2->addButton("Create button", [&]() {
        vbox->add(new gui::Button(textbox3->getText()));
    });

    // Small progress bar
    gui::HBoxLayout* hbox3 = vbox->addHBoxLayout();
    hbox3->addLabel("Small progress bar");
    gui::ProgressBar* pbar = new gui::ProgressBar(40);
    hbox3->add(pbar);

    gui::Slider* vslider = new gui::Slider(100, gui::Vertical);
    vslider->setCallback([&]() {
        pbar->setValue(vslider->getValue());
    });
    hbox->add(vslider);

    menu.addButton("Quit", [&]() {
        app.close();
    });

    sf::Texture texture;
    texture.loadFromFile("demo/sfml.png");

    sf::Sprite sprite(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setPosition(300, 360);

    // Start the application loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Send events to menu
            menu.onEvent(event);
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
