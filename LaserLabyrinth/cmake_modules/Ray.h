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

    Ray() = default;

    sf::FloatRect getRect() {
        return sf::FloatRect(line.getPosition().x, line.getPosition().y, line.getSize().x,
                line.getSize().y);
    }

    void set(int x1, int y1, int x2, int y2, double angle);

    void set(int x, int y, double angle, uint length);

};


#endif //LASERLABYRINTH_RAY_H
