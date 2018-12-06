#ifndef LASERLABYRINTH_LASERCANNON_H
#define LASERLABYRINTH_LASERCANNON_H


#include "GameObject.h"
#include "Line.h"

class LaserCannon : public GameObject {

public:

    LaserCannon() = default;

    void set(std::ifstream &fin) override;

    Line &getLine() override {}

    void rotate(int side) override {};

    void moveByX(int speed) override {};

    void moveByY(int speed) override {};

    int getYAbove() override {};

    int getYBelow() override {};

    int getXLeft() override {};

    int getXRigth() override {};

};


#endif //LASERLABYRINTH_LASERCANNON_H
