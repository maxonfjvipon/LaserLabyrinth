#ifndef LASERLABYRINTH_GAMEOBJECT_H
#define LASERLABYRINTH_GAMEOBJECT_H


#include "Transform.h"
#include "Image.h"
#include <SFML/Graphics.hpp>
#include "Line.h"

class GameObject {

public:

    std::string name;
    Transform transform;
    Image image;

    bool canReflect = false;

    GameObject() = default;

    sf::FloatRect getRect() {
        return sf::FloatRect(transform.x, transform.y, image.width * image.scale / 2,
                             image.height * image.scale / 2);
    }

    virtual Line &getLine() = 0;

    virtual void set(std::ifstream &fin) = 0;

};


#endif //LASERLABYRINTH_GAMEOBJECT_H
