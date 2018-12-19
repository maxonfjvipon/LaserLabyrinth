#include "Object.h"

void Object::set(std::ifstream &fin) {
    fin >> name;
    transform.set(fin);
    image.setParametersFromFile(fin);
    image.set(transform.x, transform.y, static_cast<ushort>(transform.rotateAngle));
}
