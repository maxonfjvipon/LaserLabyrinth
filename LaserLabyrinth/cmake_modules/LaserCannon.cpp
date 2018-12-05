#include "LaserCannon.h"
#include "Mirror.h"

void LaserCannon::set(std::ifstream &fin) {
    name = "LaserCannon";
    transform.set(fin);
    image.setParametersFromFile(fin);
    image.set(transform.x, transform.y, static_cast<ushort>(transform.rotateAngle));
}