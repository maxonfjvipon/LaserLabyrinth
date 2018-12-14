#include "MainHero.h"
#include "Mirror.h"
#include <iostream>

void MainHero::set(std::ifstream &fin) {
    transform.set(fin);
    image.setParametersFromFile(fin);

    image.set(transform.x, transform.x, static_cast<ushort>(transform.rotateAngle));

    mode = Walk;
    isStaying = true;

    name = "Hero";
}
