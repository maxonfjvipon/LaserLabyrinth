#ifndef LASERLABYRINTH_MIRROR_H
#define LASERLABYRINTH_MIRROR_H

#include <iostream>
#include "Image.h"
#include "Transform.h"

class Mirror {
public:

    Transform transform;
    Image image;

    ushort rotateSpeed{};


    Mirror(){};

    void set(std::ifstream &fin);

    void rotate(int side) {
        image.sprite.rotate(side * rotateSpeed);
    }

};


#endif //LASERLABYRINTH_MIRROR_H
