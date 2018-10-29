#ifndef LASERLABYRINTH_MAINHERO_H
#define LASERLABYRINTH_MAINHERO_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include "Mirror.h"

enum mainHeroMode {
    walk, moveMirror, rotateMirror
};

//main hero
class MainHero {
    int xPos{}, yPos{}; // position
    u_short speed = 2; //speed of walking
    u_short mode{};
    sf::Sprite heroSprite;
    u_short spriteHeight = 20; //fixme
    u_short spriteWidth = 20; //fixme

    void move(sf::Event &event);

public:
    MainHero();

    void heroMoves(sf::Event &event) {
        move(event);
    }

    sf::Sprite &getSprite(){
        return heroSprite;
    }

};


#endif //LASERLABYRINTH_MAINHERO_H
