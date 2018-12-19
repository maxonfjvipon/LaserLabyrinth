#include "Menu.h"
#include <fstream>

void Menu::actionsInMenu(float &time, Game &game, sf::RenderWindow &window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        activeButton = (activeButton + buttons.size() + 1) % buttons.size();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        activeButton = (activeButton + buttons.size() - 1) % buttons.size();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        switch (buttonsNames[activeButton]) {
            case NG_Cntrl:
                if(isMainMenu) {
                    isActive = false;
                    game.newGame();
                } else {
                    if(!isControlWindowOpen) {
//                        sf::Window
                    }
                    //todo control screen
                }
                break;
            case Cntn_Vlm:
                if(isMainMenu) {
                    //todo load and continue
                } else {
                    buttons[activeButton].setString(game.volume ? "Volume_ON" : "Volume_OFF");
                    game.volume = !game.volume;
                }
                break;
            case Vlm_MM:
                if(isMainMenu) {
                    buttons[activeButton].setString(game.volume ? "Volume_ON" : "Volume_OFF");
                    game.volume = !game.volume;
                } else {
                    //todo save the game
                    goToMain = true;
                }
                break;
            case Exit:
                window.close();
                break;
        }
    }
}

void Menu::menu(float &time, Game &game, sf::RenderWindow &window) {
    actionsInMenu(time, game, window);
    for (short i = 0; i < buttons.size(); i++) {
        buttons[i].setScale(i == activeButton ? (sf::Vector2f(2.5, 2.5)) : (sf::Vector2f(2, 2)));
        buttons[i].setFillColor(i == activeButton ? (sf::Color::Red) : (buttonsColor));
    }
}

void Menu::draw(sf::RenderWindow &window) {
    window.draw(backGround.sprite);
    window.draw(mainText);
    for (auto &button : buttons) {
        window.draw(button);
    }
}

void Menu::setMainMenu() {
    isMainMenu = true;
    goToMain = false;
    isActive = true;
    activeButton = 0;
    std::ifstream fin("files/mainMenuFile.txt");
    backGround.setParametersFromFile(fin);
    backGround.set(720, 450, 0);
    backGround.sprite.setScale(1, 1);
    buttons.resize(4);
    buttonsNames.resize(4);

    buttonsColor = sf::Color::Yellow;

    font.loadFromFile("fonts/pixel.ttf");
    mainText = setText("LASER_LABYRINTH", 100, 100, sf::Color::Magenta, 50, 2);

    std::string string;
    int x, y;
    uint size, scale;

    for (auto i = 0; i < 4; i++) {
        fin >> string >> x >> y >> size >> scale >> buttonsNames[i];
        buttons[i] = setText(string, x, y, buttonsColor, size, scale);
    }

    fin.close();
}

void Menu::setPauseMenu() {
    goToMain = false;
    isMainMenu = false;
    isActive = false;
    activeButton = 0;
    std::ifstream fin("files/pauseMenuFile.txt");

    //fixme buttons position

    buttons.resize(4);
    buttonsNames.resize(4);

    font.loadFromFile("fonts/pixel.ttf");
    mainText = setText("",0,0,sf::Color::Black,0,0);

    std::string string;
    int x, y;
    uint size, scale;

    buttonsColor = sf::Color::White;

    for(auto i = 0; i < 4; i++) {
        fin >> string >> x >> y >> size >> scale >> buttonsNames[i];
        buttons[i] = setText(string, x, y, buttonsColor, size, scale);
    }

    fin.close();
}

sf::Text Menu::setText(const std::string &string, int x, int y, const sf::Color &color, uint size,
                       uint scale) {
    sf::Text text;
    text.setFont(font);
    text.setString(string);
    text.setPosition(x, y);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(color);
    text.setCharacterSize(size);
    text.setScale(scale, scale);
    return text;
}