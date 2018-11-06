#ifndef LASERLABYRINTH_PICTURE_H
#define LASERLABYRINTH_PICTURE_H

#include <SFML/Graphics.hpp>

class Picture {

    float currentFrame = 0;

    sf::Sprite sprite;
    sf::Texture texture;

    void animatePicture(float xOffset, float yOffset, ushort spriteWidth, ushort spriteHeight,
                        ushort direction);

    void setSprite(const std::string &fileName, ushort spriteWidth, ushort spriteHeight,
                   int xPos, int yPos);

public:

    Picture() = default;

    void set(const std::string &fileName, ushort spriteWidth, ushort spriteHeight,
             int xPos, int yPos) {
        setSprite(fileName, spriteWidth, spriteHeight, xPos, yPos);
    }

    void animate(float xOffset, float yOffset, ushort spriteWidth, ushort spriteHeight,
                 ushort direction) {
        animatePicture(xOffset, yOffset, spriteWidth, spriteHeight, direction);
    }

    sf::Sprite &getSprite() {
        return sprite;
    }

};


#endif //LASERLABYRINTH_PICTURE_H
