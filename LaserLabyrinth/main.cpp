#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "cmake_modules/Level.h"
#include "cmake_modules/Menu.h"
#include "cmake_modules/Game.h"

void restartClock(sf::Clock &clock, float &time);

void actions(float &time, sf::RenderWindow &window);

void draw(sf::RenderWindow &window, Menu &mainMenu, Menu &pauseMenu, Game &game);

void fromPauseToMain(Menu &mainMenu, Menu &pauseMenu);

int main() {

    //screen geometry
    const u_short screenWidth = 1440;
    const u_short screenHeight = 900;

    float time = 0; // time
    float delay = 0.15; // time delay
    sf::Event event{}; // main event
    //window
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "LASER_LABYRINTH",
            sf::Style::Fullscreen);

    sf::Clock clock; //clock

//    main menu
    Menu mainMenu;
    mainMenu.setMainMenu();

//    pause menu
    Menu pauseMenu;
    pauseMenu.setPauseMenu();

//    game
    Game game;

    //main game loop
    while (window.isOpen()) {
        restartClock(clock, time);
        window.clear();
        if (time > delay) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            if (mainMenu.isActive) {
                mainMenu.menu(time, game, window);
            } else {
                if (pauseMenu.isActive) {
                    pauseMenu.menu(time, game, window);
                }
                game.actions(time, window);
                pauseMenu.isActive = game.isPause();
                fromPauseToMain(mainMenu,pauseMenu);
            }
            time = 0;
        }
        draw(window, mainMenu, pauseMenu, game);
        window.display();
    }

    return 0;
}

// go to main menu from pause menu
void fromPauseToMain(Menu &mainMenu, Menu &pauseMenu) {
    if(pauseMenu.goToMain) {
        mainMenu.isActive = true;
        pauseMenu.setPauseMenu();
    }
}

// drawing
void draw(sf::RenderWindow &window, Menu &mainMenu, Menu &pauseMenu, Game &game) {
    if (mainMenu.isActive) {
        mainMenu.draw(window);
        return;
    }
    game.draw(window);
    if (pauseMenu.isActive) {
        pauseMenu.draw(window);
    }
}

// set time and restart clock
void restartClock(sf::Clock &clock, float &time) {
    time += clock.getElapsedTime().asSeconds();
    clock.restart();
}