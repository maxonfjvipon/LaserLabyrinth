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

public:

    void set(std::ifstream &fin) override;

    MainHero(){}

    Line &getLine() override {
        Line line{};
        line.set(transform.x, transform.y, angle);
        return line;
    };

    bool isStaying{};
    u_short walkSpeed = 20; //speed of walking
    u_short mode{};
    ushort pushSpeed = static_cast<ushort>(walkSpeed / 2);

    ushort currentDirection = 0;

    int mirrorIndex = -1;

    int angle = 0;

};


#endif //LASERLABYRINTH_MAINHERO_H
