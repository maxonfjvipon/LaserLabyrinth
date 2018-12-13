#ifndef LASERLABYRINTH_MIRROR_H
#define LASERLABYRINTH_MIRROR_H

#include <iostream>
#include "Image.h"
#include "Transform.h"
#include "GameObject.h"
#include "Line.h"

class Mirror : public GameObject {

    void updateLineParameters();

    Line line {};

    int yAbove{}, yBelow{}, xLeft{}, xRigth{};

public:
    ushort length {};

    Line &getLine() override {
        return line;
    }

    ushort rotateSpeed{};

    Mirror() = default;

    void set(std::ifstream &fin) override;

    void rotate(int side);

    void moveByX(int speed);

    void moveByY(int speed);

    int getYAbove() {
        return yAbove;
    };

    int getYBelow() {
        return yBelow;
    }

    int getXLeft() {
        return xLeft;
    };

    int getXRigth() {
        return xRigth;
    };

};


#endif //LASERLABYRINTH_MIRROR_H
