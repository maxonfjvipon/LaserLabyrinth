#ifndef LASERLABYRINTH_TRANSFORM_H
#define LASERLABYRINTH_TRANSFORM_H

#include <iostream>
#include <fstream>

class Transform {
public:

    int x{}, y{};
    ushort rotateAngle{};


    Transform() {};

    void set(std::ifstream &fin) {
        fin >> x >> y >> rotateAngle;
    }

    Transform(int x, int y, ushort rotateAngle);

};


#endif //LASERLABYRINTH_TRANSFORM_H
