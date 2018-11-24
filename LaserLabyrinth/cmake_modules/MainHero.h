#ifndef LASERLABYRINTH_MAINHERO_H
#define LASERLABYRINTH_MAINHERO_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include "Mirror.h"
#include "Picture.h"

enum mainHeroMode {
    Walk, PushMirror, RotateMirror
};

//main hero
class MainHero {

    int xPos{}, yPos{}; // position
    bool stay = true;
    u_short speed = 30; //speed of walking
    u_short mode{};
    u_short spriteHeight = 32;
    u_short spriteWidth = 32;
    ushort currentDirection = 0;

    int mirrorIndex = -1;

    Picture picture;

    void WASD(int xOffset, int yOffset, ushort direction, int &coordinate, int speed,
              std::vector<Mirror> &mirrors, short coef);

    void RButton(std::vector<Mirror> &mirrors);

    void EButton(std::vector<Mirror> &mirrors);

    bool heroActions(sf::Event &event, std::vector<Mirror> &mirrors);

    void Stays();

public:

    MainHero();

    bool actions(sf::Event &event, std::vector<Mirror> &mirrors) {
        return heroActions(event, mirrors);
    }

    bool isMirrorOnWay(Mirror &mirror);

    void stays() {
        Stays();
    }

    sf::Sprite &getPicture() {
        return picture.getSprite();
    }


};


#endif //LASERLABYRINTH_MAINHERO_H
