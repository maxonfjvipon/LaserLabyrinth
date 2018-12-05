#ifndef LASERLABYRINTH_TRANSFORM_H
#define LASERLABYRINTH_TRANSFORM_H

#include <iostream>
#include <fstream>
#include <cmath>

class Transform {
public:

    int x{}, y{};
    short rotateAngle{};

    Transform() = default;

    void set(std::ifstream &fin) {
        fin >> x >> y >> rotateAngle;
    }

    void set(int x, int y, short angle);

};


#endif //LASERLABYRINTH_TRANSFORM_H
