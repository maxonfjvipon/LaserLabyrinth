#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "cmake_modules/LaserCannon.h"
#include "cmake_modules/MainHero.h"
#include "cmake_modules/Mirror.h"

void restartClock(sf::Clock &clock, float &time);

void userActions(float &time, sf::RenderWindow &window, MainHero &hero,
                 std::vector<Mirror> &mirrors);

void initMirrors(std::vector<Mirror> &mirrors);

int main() {

    //screen geometry
//    const u_short screenWidth = 800;
//    const u_short screenHeight = 600;
    const u_short screenWidth = 2000;
    const u_short screenHeight = 1000;

    float time = 0; //time

    //window
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "LASER_LABYRINTH");

    sf::Clock clock; //clock

    std::vector<Mirror> mirrors;
    initMirrors(mirrors);

    MainHero hero; //main hero

    //main game loop
    while (window.isOpen()) {
        restartClock(clock, time);
        window.clear();
        userActions(time, window, hero, mirrors);
        window.draw(hero.getPicture());
        for(auto &mirror : mirrors) {
            window.draw(mirror.getPicture());
        }
        window.display();
    }

    return 0;
}

// Инициализация зеркал
void initMirrors(std::vector<Mirror> &mirrors) {
    ushort mirrorsQuantity;
    std::ifstream fin("files/constructMirror.txt");
    fin >> mirrorsQuantity;
    mirrors.resize(mirrorsQuantity);
    for (auto &mirror : mirrors) {
        mirror.set(fin);
    }
    fin.close();
}

// set time and restart clock
void restartClock(sf::Clock &clock, float &time) {
    time += clock.getElapsedTime().asSeconds();
    clock.restart();
}

//user actions
void userActions(float &time, sf::RenderWindow &window, MainHero &hero,
                 std::vector<Mirror> &mirrors) {
    float delay = 0.1; //delay
    sf::Event event{};
    if (time > delay) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { //if "ESC" was pressed
                window.close();
            }
        }
        if (!hero.actions(event, mirrors)) {
            hero.stays();
        }
        time = 0;
    }
}