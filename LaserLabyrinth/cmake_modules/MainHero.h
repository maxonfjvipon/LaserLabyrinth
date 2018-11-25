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

enum mainHeroMode {
    Walk, PushMirror, RotateMirror
};

//main hero
class MainHero{
public:

    Transform transform;

    Image image;
    bool isStaying;
    u_short walkSpeed = 30; //speed of walking
    u_short mode;

    ushort currentDirection = 0;


    int mirrorIndex = -1;

    MainHero();

};


#endif //LASERLABYRINTH_MAINHERO_H
