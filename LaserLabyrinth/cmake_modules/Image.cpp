#include "Image.h"
#include <fstream>

void Image::set(int xPos, int yPos, ushort rotateAngle) {
    if (!texture.loadFromFile(textureFileName)) {
        std::cout << "Invalid loading texture from file2" << textureFileName << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, width, height));
    sprite.setOrigin(width / 2, height / 2);
    sprite.setPosition(xPos, yPos);
    sprite.setScale(scale, scale);
    if (rotateAngle != 1000) {
        sprite.setRotation(rotateAngle);
    }
}

void Image::animate(int xPos, int yPos, ushort direction, ushort &currentDirection,
                    bool isNeedToRotate) {
    currentFrame++;
    if (currentFrame >= 8) {
        currentFrame -= 8;
    }
    sprite.setTextureRect(sf::IntRect(width * (int) currentFrame, 0, width, height));
    if (isNeedToRotate) {
        while (currentDirection != direction) {
            currentDirection = static_cast<ushort>((currentDirection + 1) % 4);
            sprite.rotate(90);
        }
    }
    sprite.setPosition(xPos, yPos);
}
