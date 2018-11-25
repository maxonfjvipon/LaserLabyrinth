#include "Mirror.h"
#include <fstream>

void Mirror::set(std::ifstream &fin) {
    transform.set(fin);
    image.setParametersFromFile(fin);
    image.set(transform.x,transform.y,transform.rotateAngle);
    rotateSpeed = 2;
}
