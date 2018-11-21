#include "MainHero.h"
#include "Mirror.h"
#include <iostream>

MainHero::MainHero() {
    mode = Walk;
    stay = true;
    std::ifstream mainHeroInputFile("files/constructMainHero.txt");
    std::string textureFileName;
    mainHeroInputFile >> xPos >> yPos; // input position
    mainHeroInputFile >> textureFileName;
    picture = Picture();
    picture.set(textureFileName, spriteWidth, spriteHeight, xPos, yPos, 0);
    mainHeroInputFile.close();
}

bool MainHero::heroActions(sf::Event &event, Mirror &mirror) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        WASD(xPos, yPos, 2, xPos, -speed, mirror, -1);
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        WASD(xPos, yPos, 0, xPos, speed, mirror, 1);
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        WASD(xPos, yPos, 1, yPos, speed, mirror, 0);
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        WASD(xPos, yPos, 3, yPos, -speed, mirror, 0);
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        RButton();
        return true;
    }
    return false;
}

void MainHero::WASD(int xPos, int yPos, ushort direction, int &coordinate,
                    int speed, Mirror &mirror, short coef) {
    switch (mode) {
        case Walk:
            if (stay) {
                stay = false;
                picture.set("images/sprHeroWalk.png", spriteWidth, spriteHeight, xPos, yPos, 47);
            }
            coordinate += speed;
            picture.animate(xPos, yPos, spriteWidth, spriteHeight, direction,
                            currentDirection, 1);
            break;
        case RotateMirror:
            if (stay) {
                stay = false;
                picture.set("images/sprHeroRotateMirror.png", spriteWidth, spriteHeight, xPos, yPos,
                            47);
            }
            picture.animate(xPos, yPos, spriteWidth, spriteHeight, currentDirection,
                            currentDirection, coef);
            mirror.rotate(coef);
            break;
        case PushMirror:
            if (stay) {
                stay = false;
                picture.set("images/sprHeroPushMirror.png", spriteWidth, spriteHeight, xPos,
                            yPos, 47);
            }
            coordinate += speed;
            picture.animate(xPos, yPos, spriteWidth, spriteHeight, direction,
                            currentDirection, 1);
            break;
    }
}

//todo расстояние между героем и зеркалом
void MainHero::RButton() {
    std::cout << "R pressed" << std::endl;
    mode = (mode == RotateMirror ? Walk : RotateMirror);
    stay = true;
}

//todo расстояние между героем и зеркалом
void MainHero::EButton() {
    mode = (mode == PushMirror ? Walk : PushMirror);
    stay = true;
}

void MainHero::Stays() {
    if (!stay) {
        stay = true;
        switch (mode) {
            case Walk:
                picture.set("images/heroStays.png", spriteWidth, spriteHeight, xPos, yPos,
                            static_cast<ushort>(currentDirection * 90));
                break;
            case PushMirror:
                picture.set("images/heroPushStays.png", spriteWidth, spriteHeight, xPos, yPos,
                            static_cast<ushort>(currentDirection * 90));
                break;
            case RotateMirror:
                picture.set("images/heroRotateStays.png", spriteWidth, spriteHeight, xPos, yPos,
                            static_cast<ushort>(currentDirection * 90));
                break;
        }
    }
}
