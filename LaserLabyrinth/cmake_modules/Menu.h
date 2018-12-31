#ifndef LASERLABYRINTH_MENU_H
#define LASERLABYRINTH_MENU_H

#include "Image.h"
#include "Game.h"
#include <vector>

enum buttonIndex {
    NG_Sv, Cntn_Vlm, Vlm_MM, Exit
};

class Menu {

    sf::Font font;
    sf::Text mainText;
    sf::Color buttonsColor;
    Image backGround;
    std::vector<sf::Text> buttons;
    std::vector<short> buttonsNames;
    ushort activeButton{};

    Sound sound;

    void actionsInMenu(float &time, Game &game, sf::RenderWindow &window, ushort &volume);

    sf::Text setText(const std::string &string, int x, int y, const sf::Color &color, uint size,
                     uint scale);

    bool isMainMenu;

public:

    bool goToMain;

    Menu() = default;

    bool isActive{};

    void setMainMenu(ushort volume);

    void setPauseMenu(ushort volume);

    void menu(float &time, Game &game, sf::RenderWindow &window, ushort &volume);

    void draw(sf::RenderWindow &window);

};


#endif //LASERLABYRINTH_MENU_H
