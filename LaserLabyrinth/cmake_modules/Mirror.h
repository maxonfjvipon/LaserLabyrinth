#ifndef LASERLABYRINTH_MIRROR_H
#define LASERLABYRINTH_MIRROR_H

#include <iostream>
#include "Image.h"
#include "Transform.h"
#include "GameObject.h"
#include "Line.h"

class Mirror : public GameObject {

    void updateLineParameters();

    Line line;

    int yAbove{}, yBelow{}, xLeft{}, xRigth{};

public:
    ushort length;

    Line &getLine() override {
        return line;
    }

    ushort rotateSpeed{};

    Mirror() = default;

    void set(std::ifstream &fin) override;

    void rotate(int side) override;

    void moveByX(int speed) override;

    void moveByY(int speed) override;

    int getYAbove() override {
        return yAbove;
    };

    int getYBelow() override {
        return yBelow;
    }

    int getXLeft() override {
        return xLeft;
    };

    int getXRigth() override {
        return xRigth;
    };

};


#endif //LASERLABYRINTH_MIRROR_H
