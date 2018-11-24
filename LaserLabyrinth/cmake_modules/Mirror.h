#ifndef LASERLABYRINTH_MIRROR_H
#define LASERLABYRINTH_MIRROR_H

#include <iostream>
#include "Picture.h"

class Mirror {

    int xPos {}, yPos {};
    //todo fix this
    u_short spriteHeight = 32;
    u_short spriteWidth = 32;
    ushort rotateAngle {};
    ushort rotateSpeed = 2;

    Picture picture;

public:

    Mirror() = default;

    void set(std::ifstream &fin);

    void rotate(short coef) {
        picture.rotate(rotateSpeed * coef);
    }

    sf::Sprite &getPicture() {
        return picture.getSprite();
    }

    int getXPos() {
        return xPos;
    }

    ushort getSpriteWidth(){
        return spriteWidth;
    }

    ushort getSpriteHeigth() {
        return spriteHeight;
    }

    void moveByY(int speed);

    void moveByX(int speed);

    int getYPos() {
        return yPos;
    }

};


#endif //LASERLABYRINTH_MIRROR_H
