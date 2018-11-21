#include <iostream>
#include <random>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "cmake_modules/MainHero.h"

void restartClock(sf::Clock &clock, float &time);

void userActions(float &time, sf::RenderWindow &window, MainHero &hero, Mirror &mirror);

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

    std::ifstream mirrorFin("files/constructMirror.txt");

    Mirror mirror(mirrorFin);

    MainHero hero; //main hero

    //main game loop
    while (window.isOpen()) {
        restartClock(clock, time);
        window.clear();
        userActions(time, window, hero, mirror);
        window.draw(hero.getPicture());
        window.draw(mirror.getPicture());
        window.display();
    }

    mirrorFin.close();

    return 0;
}

// set time and restart clock
void restartClock(sf::Clock &clock, float &time) {
    time += clock.getElapsedTime().asSeconds();
    clock.restart();
}

void userActions(float &time, sf::RenderWindow &window, MainHero &hero, Mirror &mirror) {
    float delay = 0.1; //delay
    sf::Event event{};
    if (time > delay) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { //if "ESC" was pressed
                window.close();
            }
        }
        if(!hero.actions(event, mirror)) {
            hero.stays();
        }
        time = 0;
    }
}