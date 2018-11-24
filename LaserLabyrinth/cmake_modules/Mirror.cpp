#include "Mirror.h"
#include <fstream>

void Mirror::set(std::ifstream &fin) {
    fin >> xPos >> yPos >> rotateAngle;
    std::string textureFileName;
    fin >> textureFileName;
    picture = Picture();
    picture.set(textureFileName,spriteWidth,spriteHeight,xPos,yPos,rotateAngle);
}

void Mirror::moveByY(int speed) {
    yPos += speed;
    picture.getSprite().setPosition(xPos,yPos);
}

void Mirror::moveByX(int speed) {
    xPos += speed;
    picture.getSprite().setPosition(xPos,yPos);
}