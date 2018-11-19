#ifndef LASERLABYRINTH_PICTURE_H
#define LASERLABYRINTH_PICTURE_H

#include <SFML/Graphics.hpp>

class Picture {

    float currentFrame = 0;

    sf::Sprite sprite;
    sf::Texture texture;

    void animatePicture(int xPos, int yPos, ushort spriteWidth, ushort spriteHeight,
                        ushort direction, ushort &currentDirection);

    void setSprite(const std::string &fileName, ushort spriteWidth, ushort spriteHeight,
                   int xPos, int yPos, ushort rotation);



public:

    bool isPictureSet{};

    Picture() = default;

    void set(const std::string &fileName, ushort spriteWidth, ushort spriteHeight,
             int xPos, int yPos, ushort rotation) {
        setSprite(fileName, spriteWidth, spriteHeight, xPos, yPos, rotation);
    }

    void animate(int xPos, int yPos, ushort spriteWidth, ushort spriteHeight,
                 ushort direction, ushort &currentDirection) {
        animatePicture(xPos, yPos, spriteWidth, spriteHeight, direction, currentDirection);
    }

    sf::Sprite &getSprite() {
        return sprite;
    }

};


#endif //LASERLABYRINTH_PICTURE_H
