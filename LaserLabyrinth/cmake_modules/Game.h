#ifndef LASERLABYRINTH_GAME_H
#define LASERLABYRINTH_GAME_H

#include <iostream>
#include "Level.h"
#include <SFML/Audio.hpp>

class Game {

    sf::Music music;
    std::string musicNames[10];

    std::string loadFile = "files/loadFile.txt";

    Level level;

    void checkMusicStatus();

    bool gameOver();

public:

    bool isGameOver = false;

    bool isActive = false;

    ushort _level;

    Game() = default;

    void newGame(ushort volume);

    void saveGame();

    void continueGame(ushort volume);

    void actions(float &time, sf::RenderWindow &window, ushort volume);

    void draw(sf::RenderWindow &window);

    bool isPause() {
        return level.isPause;
    }

    sf::Music &getMusic() {
        return music;
    }

};


#endif //LASERLABYRINTH_GAME_H
