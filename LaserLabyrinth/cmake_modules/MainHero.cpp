#include "MainHero.h"
#include "Mirror.h"
#include <iostream>

//Конструктор
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

//Кнопки нажаты?
bool MainHero::heroActions(sf::Event &event, std::vector<Mirror> &mirrors) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        WASD(xPos, yPos, 2, xPos, -speed, mirrors, -1);
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        WASD(xPos, yPos, 0, xPos, speed, mirrors, 1);
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        WASD(xPos, yPos, 1, yPos, speed, mirrors, 0);
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        WASD(xPos, yPos, 3, yPos, -speed, mirrors, 0);
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        RButton(mirrors);
        return true;
    }
    return false;
}

//Обработка нажатий на WASD
void MainHero::WASD(int xPos, int yPos, ushort direction, int &coordinate,
                    int speed, std::vector<Mirror> &mirrors, short coef) {
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
            mirrors[mirrorIndex].rotate(coef);
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

//Обработка нажатий на кнопку R
void MainHero::RButton(std::vector<Mirror> &mirrors) {
    if(mode == RotateMirror) {
        mode = Walk;
        stay = true;
        mirrorIndex = -1;
        return;
    }

    if(mode == PushMirror) {
        mode = RotateMirror;
        stay = true;
        return;
    }

    for(ushort i = 0; i < mirrors.size(); i++) {
        if(isMirrorOnWay()) {
            mirrorIndex = i;
            break;
        }
    }
    if(mirrorIndex == -1) {
        return;
    }

    mode = RotateMirror;
    stay = true;

}

//Обработка нажатий на кнопку Е
void MainHero::EButton() {
    mode = (mode == PushMirror ? Walk : PushMirror);
    stay = true;
}

//Герой неподвижен
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

//todo доделать
//Есть ли зеркало перед героем?
bool MainHero::isMirrorOnWay() {
    return false;
}
