#include "MainHero.h"
#include "Mirror.h"
#include <iostream>

//Конструктор
MainHero::MainHero() {
    std::ifstream fin("files/constructMainHero.txt");

    transform.set(fin);
    image.setParametersFromFile(fin);

    image.set(transform.x,transform.x, transform.rotateAngle);

    mode = Walk;
    isStaying = true;

    fin.close();
}