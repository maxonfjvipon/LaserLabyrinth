#ifndef LASERLABYRINTH_IMAGE_H
#define LASERLABYRINTH_IMAGE_H

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Transform.h"

class Image {
public:

    sf::Texture texture;
    sf::Sprite sprite;

    std::string textureFileName;

    float currentFrame = 0;

    ushort width, height, scale = 7;

    Image() {};

    void setParametersFromFile(std::ifstream &fin) {
        fin >> width >> height >> textureFileName;
    }

    void setParameters(const std::string &fileName, ushort width, ushort height) {
        textureFileName = fileName;
        this->width = width;
        this->height = height;
    }

    sf::FloatRect getRect(Transform transform) {
        return sf::FloatRect(transform.x, transform.y, width, height);
    }

    void animate(int x, int y, ushort direction, ushort &currentDirection,
                 bool isNeedToRotate);

    void set(int x, int y, ushort rotateAngle);


};


#endif //LASERLABYRINTH_IMAGE_H
