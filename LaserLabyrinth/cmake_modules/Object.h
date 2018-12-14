#ifndef LASERLABYRINTH_OBJECT_H
#define LASERLABYRINTH_OBJECT_H


#include "GameObject.h"

class Object : public GameObject {

public:

    Line &getLine() override {
        Line line{};
        line.set(transform.x, transform.y, static_cast<short>(image.width > image.height ? 0 : 90));
        return line;
    };

    void set(std::ifstream &fin) override;


};


#endif //LASERLABYRINTH_OBJECT_H
