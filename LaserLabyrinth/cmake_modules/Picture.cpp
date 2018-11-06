#include "Picture.h"
#include <iostream>

void Picture::animatePicture(float xOffset, float yOffset,
                             ushort spriteWidth, ushort spriteHeight, ushort direction) {
    currentFrame += 0.5;
    if (currentFrame >= 8) {
        currentFrame -= 8;
    }
    sprite.setTextureRect(sf::IntRect(spriteWidth * (int) currentFrame, 0,
                                      spriteWidth, spriteHeight));
    sprite.move(xOffset, yOffset);
}

void Picture::setSprite(const std::string &fileName, ushort spriteWidth, ushort spriteHeight,
                        int xPos, int yPos) {
    if (!texture.loadFromFile(fileName)) {
        std::cout << "Invalid loading texture from file" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, spriteWidth, spriteHeight));
    sprite.move(xPos, yPos);
    sprite.setScale(10, 10); //todo delete this
}
