#ifndef LASERLABYRINTH_GAMEFIELD_H
#define LASERLABYRINTH_GAMEFIELD_H

#include <SFML/Graphics.hpp>

#include "MainHero.h"
#include "Mirror.h"
#include "GameObject.h"
#include "LaserCannon.h"
#include "Ray.h"
#include "Object.h"

class GameField {

    std::vector<Ray> rays;

    Image map;

    Line ray;

    MainHero hero;
    std::vector<GameObject *> gameObjects;

    ushort laserCannonIndex;
    ushort mirrorsQuantity;
    ushort distanceForInteract = static_cast<ushort>(50 * hero.image.scale);

    void setRays();

    bool isRayCollideNow = false;

    bool isDirectionCorrect(Line &ray, Line &obj);

    bool wasButtonPressed(sf::Event &event);

    bool collider();

    template<class type>
    void rayCollideWithObject(Ray &_ray, type &object, int &mX, int &mY);

    bool rayCollider(Ray &_ray, int mX, int mY);

    bool isMirrorOnHerosWay(Mirror *mirror);

    template <class type>
    bool getIntersectionPoint(type &object, Line &intersectPoint, Line &_ray);

    void noActions();

    bool drawAnyRay();

    void WASD(ushort direction);

    void R();

    void E();

public:

    GameField();

    void draw(sf::RenderWindow &window);

    void actions(sf::Event &event);

};


#endif //LASERLABYRINTH_GAMEFIELD_H
