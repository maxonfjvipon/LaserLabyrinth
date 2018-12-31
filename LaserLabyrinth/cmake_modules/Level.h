#ifndef LASERLABYRINTH_LEVEL_H
#define LASERLABYRINTH_LEVEL_H

#include <SFML/Graphics.hpp>

#include "MainHero.h"
#include "Mirror.h"
#include "GameObject.h"
#include "LaserCannon.h"
#include "Ray.h"
#include "Object.h"
#include "Sound.h"

class Level {

    sf::Text doorText;
    sf::Font font;

    sf::Text modeText;

    ushort currentLevel;

    std::vector<Ray> rays;
    std::vector<Sound> stepSounds;
    std::vector<Sound> sounds;

    Image map;

    Line ray{};

    MainHero hero;
    std::vector<GameObject *> gameObjects;

    ushort laserCannonIndex{};
    ushort mirrorsQuantity{};
    ushort distanceForInteract = static_cast<ushort>(40 * hero.image.scale);

    bool isDoorOpen = false;

    void setRays();

    bool isRayCollideNow = false;

    bool isDirectionCorrect(Line &ray, Line &obj);

    bool wasButtonPressed();

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

    void F();

public:

    bool isPause;

    Level() = default;

    void set(const std::string &levelFileName, ushort level, ushort volume);

    void draw(sf::RenderWindow &window);

    void actions(ushort volume);

    void save(const std::string &fileName);

    bool checkNextLevel(ushort level) {
        return level != currentLevel;
    }

};


#endif //LASERLABYRINTH_LEVEL_H
