#ifndef LASERLABYRINTH_MAINHERO_H
#define LASERLABYRINTH_MAINHERO_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include "Mirror.h"
#include "../Animation.h"

enum mainHeroMode {
    walk, moveMirror, rotateMirror
};

//main hero
class MainHero {
    int xPos{}, yPos{}; // position
    u_short speed = 2; //speed of walking
    u_short mode{};
    u_short spriteHeight = 15; //fixme
    u_short spriteWidth = 24; //fixme

    void move(sf::Event &event, float time);

public:

    Animation animation;

    MainHero();

    void heroMoves(sf::Event &event, float time) {
        move(event, time);
    }

    sf::Sprite getSprite(){
        return animation.sprite;
    }

};


#endif //LASERLABYRINTH_MAINHERO_H
