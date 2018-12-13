#ifndef LASERLABYRINTH_LASERCANNON_H
#define LASERLABYRINTH_LASERCANNON_H


#include "GameObject.h"
#include "Line.h"

class LaserCannon : public GameObject {

public:

    LaserCannon() = default;

    void set(std::ifstream &fin) override;

    Line &getLine() override {}

};


#endif //LASERLABYRINTH_LASERCANNON_H
