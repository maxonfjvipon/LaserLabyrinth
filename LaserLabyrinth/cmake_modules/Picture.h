#ifndef LASERLABYRINTH_PICTURE_H
#define LASERLABYRINTH_PICTURE_H

#include <SFML/Graphics.hpp>

class Picture {

    float currentFrame = 0;

    sf::Sprite sprite;
    sf::Texture texture;

    void animatePicture(int xPos, int yPos, ushort spriteWidth, ushort spriteHeight,
                        ushort direction, ushort &currentDirection, short coef);

    void setSprite(const std::string &fileName, ushort spriteWidth, ushort spriteHeight,
                   int xPos, int yPos, ushort rotation);

public:

    bool isPictureSet{};

    Picture() = default;

    void set(const std::string &fileName, ushort spriteWidth, ushort spriteHeight,
             int xPos, int yPos, ushort rotation) {
        setSprite(fileName, spriteWidth, spriteHeight, xPos, yPos, rotation);
    }

    void rotate(short rotateSpeed){
        sprite.rotate(rotateSpeed);
    }

    void animate(int xPos, int yPos, ushort spriteWidth, ushort spriteHeight,
                 ushort direction, ushort &currentDirection, short coef) {
        animatePicture(xPos, yPos, spriteWidth, spriteHeight, direction, currentDirection, coef);
    }

    sf::Sprite &getSprite() {
        return sprite;
    }

};


#endif //LASERLABYRINTH_PICTURE_H
