#include "Line.h"
#include <cmath>

void Line::set(int x, int y, short intAngle) {
    this->x = x;
    this->y = y;
    this->angle = intAngle * M_PI / 180;
    k = tan(this->angle);
    b = y - k * x;
}
