#ifndef LASERLABYRINTH_MAINHERO_H
#define LASERLABYRINTH_MAINHERO_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include "Mirror.h"
#include "Transform.h"
#include "Image.h"
#include "Line.h"
#include "GameObject.h"

enum mainHeroMode {
    Walk, PushMirror, RotateMirror
};

//main hero
class MainHero : public GameObject{

    void set(std::ifstream &fin) override {};

    void rotate(int side) override {};

    void moveByX(int speed) override {}

    void moveByY(int speed) override {} ;


    int getYAbove() override {};

    int getYBelow() override {};

    int getXLeft() override {};

    int getXRigth() override {};

public:

    Line &getLine() override {
        Line line{};
        line.set(transform.x, transform.y, 0);
        return line;
    };

    bool isStaying{};
    u_short walkSpeed = 30; //speed of walking
    u_short mode{};
    ushort pushSpeed = static_cast<ushort>(walkSpeed / 2);

    ushort currentDirection = 0;

    int mirrorIndex = -1;

    MainHero();


};


#endif //LASERLABYRINTH_MAINHERO_H
