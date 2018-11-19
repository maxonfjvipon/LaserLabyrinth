#include "MainHero.h"
#include <iostream>

MainHero::MainHero() {
    mode = Walk;
    stay = true;
    std::ifstream mainHeroInputFile("files/constructMainHero.txt");
    std::string textureFileName;
    mainHeroInputFile >> xPos >> yPos; // input position
    mainHeroInputFile >> textureFileName;
    textureFileName += ".png";
    picture = Picture();
    picture.set(textureFileName, spriteWidth, spriteHeight, xPos, yPos, 0);
    mainHeroInputFile.close();
}

void MainHero::heroActions(sf::Event &event) {
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::D;

    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::W:
                WASD(270, 0, -speed, 3, yPos, -speed);
                break;
            case sf::Keyboard::A:
                WASD(180, -speed, 0, 2, xPos, -speed);
                break;
            case sf::Keyboard::S:
                WASD(90, 0, speed, 1, yPos, speed);
                break;
            case sf::Keyboard::D:
                WASD(0, xPos, yPos, 0, xPos, speed);
                break;
            case sf::Keyboard::R:
                RButton();
                break;
            case sf::Keyboard::E:
                break;
        }
    } else { //todo fixme !!! нету анимации!

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
            }
        }
    }
}


void MainHero::WASD(ushort angle, int xPos, int yPos, ushort direction, int &coordinate,
                    int speed) {
    switch (mode) {
        case Walk:
            if (stay) {
                stay = false;
                picture.set("images/sprHeroWalk.png", spriteWidth, spriteHeight, xPos, yPos, angle);
            }
            coordinate += speed;
            picture.animate(xPos, yPos, spriteWidth, spriteHeight, direction,
                            currentDirection);
            break;
        case RotateMirror:
            if (stay) {
                stay = false;
                picture.set("images/sprHeroRotateMirror.png", spriteWidth, spriteHeight, xPos,
                            yPos, angle);
            }
            //указатель на зеркало.rotate(rotateDirection);
            break;
        case PushMirror:
            if (stay) {
                stay = false;
                picture.set("images/sprHeroPushMirror.png", spriteWidth, spriteHeight, xPos,
                            yPos, angle);
            }
            coordinate += speed;
            picture.animate(xPos, yPos, spriteWidth, spriteHeight, direction,
                            currentDirection);
            break;
    }
}

//todo расстояние между героем и зеркалом
void MainHero::RButton() {
    mode = (mode == RotateMirror ? Walk : RotateMirror);
    stay = true;
}

//todo расстояние между героем и зеркалом
void MainHero::EButton() {
    mode = (mode == PushMirror ? Walk : PushMirror);
    stay = true;
}
