#include "Game.h"
#include "Level.h"
#include <random>
#include <ctime>

ushort getRandomNumber() {
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<ushort> distribution(0,10);
    return distribution(generator);
}

void Game::newGame(ushort volume) {
    isActive = true;
    std::ifstream fin("files/musicNames.txt");
    for (auto &musicName : musicNames) {
        fin >> musicName;
    }
    music.openFromFile(musicNames[getRandomNumber()]);
    _level = 1;
    level.set("files/level1.txt", _level, volume);
    music.play();
    fin.close();

    std::fstream fout("files/continueGame.txt", std::ios::trunc);
    fout << _level;
    fout.close();
}



void Game::actions(float &time, sf::RenderWindow &window, ushort volume) {
    level.actions(volume);
    if (level.checkNextLevel(_level)) {
        if(gameOver()) {
            return;
        }
        level.set("files/level" + std::to_string(_level) + ".txt", _level, volume);
    }
    music.setVolume(volume == 0 ? 0 : 20);
    checkMusicStatus();
}

void Game::draw(sf::RenderWindow &window) {
    level.draw(window);
}

void Game::checkMusicStatus() {
    if(isActive && !music.getStatus()) {
        music.openFromFile(musicNames[getRandomNumber()]);
        music.play();
    }
}

void Game::continueGame(ushort volume) {
    isActive = true;
    std::ifstream fin("files/musicNames.txt");

    for (auto &musicName : musicNames) {
        fin >> musicName;
    }
    music.openFromFile(musicNames[random() % 10]);
    fin.close();
    fin.open("files/continueFile.txt");
    fin >> _level;
    level.set("files/loadFile.txt", _level, volume);
    music.play();
    fin.close();
}

void Game::saveGame() {
    std::ofstream fout("files/continueFile.txt", std::ios::trunc);
    fout << _level;
    level.save(loadFile);
    fout.close();
}

bool Game::gameOver() {
    _level++;
    if(_level > 5) {
        isGameOver = true;
        isActive = false;
        music.stop();
        return true;
    }
    return false;
}
