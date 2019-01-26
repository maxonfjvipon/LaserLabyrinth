#include "Menu.h"
#include <fstream>

void Menu::actionsInMenu(float &time, Game &game, sf::RenderWindow &window, ushort &volume) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        activeButton = (activeButton + buttons.size() + 1) % buttons.size();
        sound.play();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        activeButton = (activeButton + buttons.size() - 1) % buttons.size();
        sound.play();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        sound.play();
        switch (buttonsNames[activeButton]) {
            case NG_Sv:
                if(isMainMenu) {
                    isActive = false;
                    game.newGame(volume);
                } else {
                    game.saveGame();
                }
                break;
            case Cntn_Vlm:
                if(isMainMenu) {
                    isActive = false;
                    game.continueGame(volume);
                } else {
                    volume = static_cast<ushort>(volume != 0 ? 0 : 20);
                }
                break;
            case Vlm_MM:
                if(isMainMenu) {
                    volume = static_cast<ushort>(volume != 0 ? 0 : 20);
                } else {
                    goToMain = true;
                    game.isActive = false;
                    game.getMusic().stop();
                }
                break;
            case Exit:
                window.close();
                break;
        }
    }
}

void Menu::menu(float &time, Game &game, sf::RenderWindow &window, ushort &volume) {
    actionsInMenu(time, game, window, volume);
    for (short i = 0; i < buttons.size(); i++) {
        buttons[i].setScale(i == activeButton ? (sf::Vector2f(2.5, 2.5)) : (sf::Vector2f(2, 2)));
        buttons[i].setFillColor(i == activeButton ? (sf::Color::Red) : (buttonsColor));
    }
    buttons[(isMainMenu ? 2 : 1)].setString(volume != 0 ? "Volume_ON" : "Volume_OFF");
    sound.setVolume(volume);
}

void Menu::draw(sf::RenderWindow &window) {
    window.draw(backGround.sprite);
    window.draw(mainText);
    for (auto &button : buttons) {
        window.draw(button);
    }
}

void Menu::setMainMenu(ushort volume) {

    sound.setArrowsSound(volume);

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

void Menu::setPauseMenu(ushort volume) {

    sound.setArrowsSound(volume);

    goToMain = false;
    isMainMenu = false;
    isActive = false;
    activeButton = 0;
    std::ifstream fin("files/pauseMenuFile.txt");

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