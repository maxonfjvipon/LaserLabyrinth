#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "cmake_modules/GameField.h"

void restartClock(sf::Clock &clock, float &time);

void actions(float &time, sf::RenderWindow &window, GameField &gameField);

int main() {

    //screen geometry
    const u_short screenWidth = 2560;
    const u_short screenHeight = 1600;

    float time = 0; //time
    //window
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "LASER_LABYRINTH");

    sf::Clock clock; //clock

    GameField gameField;
    gameField.getView().reset(sf::FloatRect(0,0,screenWidth,screenHeight));

    //main game loop
    while (window.isOpen()) {
        restartClock(clock, time);
        window.setView(gameField.getView());
        window.clear();
        actions(time,window, gameField);
        gameField.draw(window);
        window.display();
    }

    return 0;
}

void actions(float &time, sf::RenderWindow &window, GameField &gameField) {
    float delay = 0.1; //delay
    sf::Event event{};
    if(time > delay) {
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }
        gameField.actions(event);
        time = 0;
    }
}

// set time and restart clock
void restartClock(sf::Clock &clock, float &time) {
    time += clock.getElapsedTime().asSeconds();
    clock.restart();
}