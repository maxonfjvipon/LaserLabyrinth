#include "Ray.h"
#include <cmath>

void Ray::set(int x1, int y1, int x2, int y2, double angle) {
    Line::set(x1, y1, static_cast<short>(angle * 180 / M_PI));
    ushort width = 10;
    auto length = static_cast<ushort>(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
    line.setPosition(x1, y1);
    line.setSize(sf::Vector2f(length, width));
    line.setOrigin(0, width / 2);
    line.setFillColor(sf::Color::Yellow);
    line.setRotation(static_cast<float>(angle * 180 / M_PI));
}

void Ray::set(int x, int y, double angle, uint length) {
    Line::set(x, y, static_cast<short>(angle * 180 / M_PI));
    ushort width = 10;
    line.setPosition(x, y);
    line.setSize(sf::Vector2f(length, width));
    line.setOrigin(0, width / 2);
    line.setFillColor(sf::Color::Yellow);
    line.rotate(static_cast<float>(angle * 180 / M_PI));
}
