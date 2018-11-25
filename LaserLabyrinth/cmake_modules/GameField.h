#ifndef LASERLABYRINTH_GAMEFIELD_H
#define LASERLABYRINTH_GAMEFIELD_H

#include "MainHero.h"
#include "Mirror.h"

class GameField {

    MainHero hero;
    std::vector<Mirror> mirrors;
    ushort mirrorsQuantity;
    ushort distanseForInteract = static_cast<ushort>(50 * hero.image.scale);

    bool wasButtonPressed(sf::Event &event);

    template <class type1, class type2>
    bool collide(type1 &object1,type2 &object2);

    bool isMirrorOnHerosWay(Mirror &mirror);

    void noActions();

    void WASD(ushort direction);

    void R();

    void E();

public:

    GameField();

    void draw(sf::RenderWindow &window);

    void actions(sf::Event &event){
        if(!wasButtonPressed(event)) {
            noActions();
        }
    }


};


#endif //LASERLABYRINTH_GAMEFIELD_H
