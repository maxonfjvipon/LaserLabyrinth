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

void draw(sf::RenderWindow &window, Menu &mainMenu, Menu &pauseMenu, Game &game);

void fromPauseToMain(Menu &mainMenu, Menu &pauseMenu, ushort volume);

void checkGameOver(Game &game, Menu &mainMenu);

int main() {

    //screen geometry
    const u_short screenWidth = 1440;
    const u_short screenHeight = 900;

    float time = 0; // time
    float delay = 0.12; // time delay

    ushort volume = 0; // volume

    sf::Event event{}; // main event
    //window
//    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "LASER_LABYRINTH",
//            sf::Style::Fullscreen);

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "LASER_LABYRINTH");

    sf::Clock clock; //clock

//    main menu
    Menu mainMenu;
    mainMenu.setMainMenu(volume);

//    pause menu
    Menu pauseMenu;
    pauseMenu.setPauseMenu(volume);

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
                mainMenu.menu(time, game, window, volume);
            } else {
                if (pauseMenu.isActive) {
                    pauseMenu.menu(time, game, window, volume);
                }
                game.actions(time, window, volume);
                checkGameOver(game, mainMenu);
                pauseMenu.isActive = game.isPause();
                fromPauseToMain(mainMenu,pauseMenu, volume);
            }
            time = 0;
        }
        draw(window, mainMenu, pauseMenu, game);
        window.display();
    }

    return EXIT_SUCCESS;
}

// go to main menu from pause menu
void fromPauseToMain(Menu &mainMenu, Menu &pauseMenu, ushort volume) {
    if(pauseMenu.goToMain) {
        mainMenu.isActive = true;
        pauseMenu.setPauseMenu(volume);
    }
}

// if game was over go to main menu
void checkGameOver(Game &game, Menu &mainMenu) {
    if(game.isGameOver) {
        mainMenu.isActive = true;
        game.isGameOver = false;
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