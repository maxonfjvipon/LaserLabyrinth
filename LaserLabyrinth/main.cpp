#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "cmake_modules/MainHero.h"

void restartClock(sf::Clock& clock, float &time);

void userActions(sf::Event &event, float &time, sf::RenderWindow &window, MainHero &hero);

int main() {

    //screen geometry
    const u_short screenWidth = 800;
    const u_short screenHeight = 600;

    float time = 0; //time


    //window
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "LASER_LABYRINTH");

    sf::Event event{}; //event
    sf::Clock clock; //clock

    MainHero hero; //main hero

    //main game loop
    while (window.isOpen()) {
        restartClock(clock,time);
        userActions(event,time,window,hero);
        window.clear();
        window.draw(hero.animation.sprite);
        window.display();
    }
    return 0;
}

// set time and restart clock
void restartClock(sf::Clock &clock, float &time){
    time += clock.getElapsedTime().asMilliseconds();
    clock.restart();
}

void userActions(sf::Event &event, float &time, sf::RenderWindow &window, MainHero &hero){
    float delay = 0.1; //delay
    if(time > delay){
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) { //if "ESC" was pressed
                window.close();
                break;
            }
            if(event.type == sf::Event::KeyPressed) { //fixme
                hero.heroMoves(event,time, window);
            }
        }
        time = 0;
    }
}