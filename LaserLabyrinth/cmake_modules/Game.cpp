#include "Game.h"
#include "Level.h"

void Game::newGame() {
    _level = 1;
    level.set("files/level1.txt", _level);
}

void Game::actions(float &time, sf::RenderWindow &window) {
    level.actions();
    if(level.checkNextLevel(_level)) { //todo check game over
        nextLevel();
    }
}

void Game::draw(sf::RenderWindow &window) {
    level.draw(window);
}

void Game::nextLevel() {
    _level++;
    level.set("files/level" + std::to_string(_level) + ".txt", _level);
}
