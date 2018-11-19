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
    u_short speed = 20; //speed of walking
    u_short mode{};
    u_short spriteHeight = 32;
    u_short spriteWidth = 32;
    ushort  currentDirection = 0;

    Picture picture;

    void WASD(ushort angle, int xOffset, int yOffset, ushort direction, int &coordinate, int speed);

    void RButton();

    void EButton();

    bool heroActions(sf::Event &event);

    void Stays();

public:

    MainHero();

    bool actions(sf::Event &event) {
        return heroActions(event);
    }

    void stays(){
        Stays();
    }

    sf::Sprite &getPicture(){
        return picture.getSprite();
    }


};


#endif //LASERLABYRINTH_MAINHERO_H
