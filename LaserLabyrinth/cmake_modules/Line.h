#ifndef LASERLABYRINTH_LINE_H
#define LASERLABYRINTH_LINE_H


#include <SFML/Graphics.hpp>

class Line {

public:

    double x, y, b, angle, k;

    Line() = default;

    void set(int x, int y, short intAngle);

};


#endif //LASERLABYRINTH_LINE_H
