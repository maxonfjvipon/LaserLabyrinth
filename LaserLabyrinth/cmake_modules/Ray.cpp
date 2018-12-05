#include "Ray.h"
#include <cmath>

void Ray::set(int x1, int y1, int x2, int y2, double angle) {
//    if (!texture.loadFromFile("images/ray.png")) {
//        std::cout << "Can not load ray texture from file" << std::endl;
//        return;
//    }
    ushort width = 6;
    auto length = static_cast<ushort>(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
    line.setPosition(x1, y1);
    line.setSize(sf::Vector2f(length,width));
    line.setOrigin(0, width / 2);
    line.setFillColor(sf::Color::Yellow);
//    line.setTexture(&texture);
    line.rotate(static_cast<float>(angle * 180 / M_PI));
}
