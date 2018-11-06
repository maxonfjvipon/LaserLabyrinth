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
    walk, moveMirror, rotateMirror
};

//main hero
class MainHero {

    int xPos{}, yPos{}; // position
    u_short speed = 10; //speed of walking
//    u_short mode{};
    u_short spriteHeight = 24; //fixme
    u_short spriteWidth = 24; //fixme

    void move(sf::Event &event);

public:

    Picture picture;

    MainHero();

    void heroMoves(sf::Event &event) {
        move(event);
    }

    sf::Sprite &getPicture(){
        return picture.getSprite();
    }

};


#endif //LASERLABYRINTH_MAINHERO_H
