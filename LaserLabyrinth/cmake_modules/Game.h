#ifndef LASERLABYRINTH_GAME_H
#define LASERLABYRINTH_GAME_H

#include <iostream>
#include "Level.h"

class Game {

   Level level;

   void nextLevel();

public:

    bool volume = false;

    ushort _level;

    Game() = default;

    void newGame();

    void actions(float &time, sf::RenderWindow &window);

    void draw(sf::RenderWindow &window);

    bool isPause() {
        return level.isPause;
    }

};


#endif //LASERLABYRINTH_GAME_H
