#ifndef LASERLABYRINTH_GAMEFIELD_H
#define LASERLABYRINTH_GAMEFIELD_H

#include <SFML/Graphics.hpp>

#include "MainHero.h"
#include "Mirror.h"
#include "GameObject.h"
#include "LaserCannon.h"
#include "Ray.h"

class GameField {

    std::vector<Ray> rays;

    Line ray;

    MainHero hero;
    std::vector<GameObject *> gameObjects;

    ushort laserCannonIndex;
    ushort mirrorsQuantity;
    ushort distanceForInteract = static_cast<ushort>(30 * hero.image.scale);

    sf::View view;

    bool isDirectionCorrect(Line &mirror);

    bool wasButtonPressed(sf::Event &event);

    bool collider();

    bool isMirrorOnHerosWay(GameObject &gameObject);

    bool getIntersectionPoint(ushort index, Line &mirror);

    void noActions();

    void drawAnyRay();

    void WASD(ushort direction);

    void R();

    void E();

public:

    GameField();

    void draw(sf::RenderWindow &window);

    void actions(sf::Event &event) {
        if (wasButtonPressed(event)) {
            view.setCenter(hero.transform.x, hero.transform.y);
            return;
        }
        noActions();
        drawAnyRay();
    }

    sf::View &getView() {
        return view;
    }

};


#endif //LASERLABYRINTH_GAMEFIELD_H
