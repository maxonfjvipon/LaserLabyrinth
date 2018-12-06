#ifndef LASERLABYRINTH_RAY_H
#define LASERLABYRINTH_RAY_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Line.h"

class Ray : public Line {

public:

    sf::RectangleShape line;
    sf::Texture texture;

    bool reflectingNow = false;

    Ray() = default;

    void set(int x1, int y1, int x2, int y2, double angle);

};


#endif //LASERLABYRINTH_RAY_H
