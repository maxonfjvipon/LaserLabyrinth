#include "Mirror.h"
#include <fstream>

void Mirror::set(std::ifstream &fin) {
    name = "Mirror";
    transform.set(fin);
    image.setParametersFromFile(fin);
    image.set(transform.x, transform.y, static_cast<ushort>(transform.rotateAngle));
    rotateSpeed = 1;
    length = static_cast<ushort>(image.scale * 20); //fixme
    updateLineParameters();
}

void Mirror::rotate(int side) {
    image.sprite.rotate(side * rotateSpeed);
    transform.rotateAngle = static_cast<short>(image.sprite.getRotation());
    updateLineParameters();
}

void Mirror::updateLineParameters() {
    line.set(transform.x, transform.y, transform.rotateAngle);
    yAbove = static_cast<int>(transform.y + length / 2 * sin(transform.rotateAngle * M_PI / 180));
    yBelow = static_cast<int>(transform.y - length / 2 * sin(transform.rotateAngle * M_PI / 180));
    if(yBelow > yAbove) {
        std::swap(yBelow,yAbove);
    }
    xLeft = static_cast<int>(transform.x - length / 2 * cos(transform.rotateAngle * M_PI / 180));
    xRigth = static_cast<int>(transform.x + length / 2 * cos(transform.rotateAngle * M_PI / 180));
    if(xLeft > xRigth) {
        std::swap(xLeft,xRigth);
    }
}

void Mirror::moveByX(int speed) {
    transform.x += speed;
    updateLineParameters();
}

void Mirror::moveByY(int speed) {
    transform.y += speed;
    updateLineParameters();
}