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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        EButton(mirrors);
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
                picture.set("images/sprHeroWalk.png", spriteWidth, spriteHeight, xPos,
                            yPos, 47);
            }
            if (currentDirection == 1 || currentDirection == 3) {
                mirrors[mirrorIndex].moveByY(speed);
            } else if (currentDirection == 0 || currentDirection == 2){
                mirrors[mirrorIndex].moveByX(speed);
            }
            std::cout << "xPos: " << mirrors[mirrorIndex].getXPos() << std::endl;
            coordinate += speed;
            picture.animate(xPos, yPos, spriteWidth, spriteHeight, direction,
                            currentDirection, 1);
            break;
    }
}

//Обработка нажатий на кнопку R
void MainHero::RButton(std::vector<Mirror> &mirrors) {
    std::cout << "R pressed" << std::endl;
    if (mode == RotateMirror) {
        mode = Walk;
        stay = true;
        mirrorIndex = -1;
        return;
    }

    if (mode == PushMirror) {
        mode = RotateMirror;
        stay = true;
        return;
    }

    for (ushort i = 0; i < mirrors.size(); i++) {
        if (isMirrorOnWay(mirrors[i])) {
            mirrorIndex = i;
            break;
        }
    }
    if (mirrorIndex == -1) {
        return;
    }

    mode = RotateMirror;
    stay = true;

}

//todo сделать красивую анимацию толкания зеркала
//todo расстояние между героем и зеркалом
//Обработка нажатий на кнопку Е
void MainHero::EButton(std::vector<Mirror> &mirrors) {
    std::cout << "E pressed" << std::endl;
    if (mode == PushMirror) {
        mode = Walk;
        stay = true;
        mirrorIndex = -1;
        return;
    }

    if (mode == RotateMirror) {
        mode = PushMirror;
        stay = true;
        return;
    }

    for (ushort i = 0; i < mirrors.size(); i++) {
        if (isMirrorOnWay(mirrors[i])) {
            mirrorIndex = i;
            break;
        }
    }

    if (mirrorIndex == -1) {
        return;
    }

    mode = PushMirror;
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
            case PushMirror: //fixme
                picture.set("images/heroStays.png", spriteWidth, spriteHeight, xPos, yPos,
                            static_cast<ushort>(currentDirection * 90));
                break;
            case RotateMirror:
                picture.set("images/heroRotateStays.png", spriteWidth, spriteHeight, xPos, yPos,
                            static_cast<ushort>(currentDirection * 90));
                break;
        }
    }
}

//todo оптимальное расстояние до зеркала, зависимость от sprite.scale
//Есть ли зеркало перед героем?
bool MainHero::isMirrorOnWay(Mirror &mirror) {
    switch (currentDirection) {
        case 0: //Right
            if (mirror.getXPos() - xPos <= spriteWidth / 2 + mirror.getSpriteWidth() / 2 + 50) {
                if (abs(mirror.getYPos() - yPos) <= 20) {
                    xPos = mirror.getXPos() - mirror.getSpriteWidth() / 2 - spriteWidth / 2;
                    yPos = mirror.getYPos();
                    return true;
                }
            }
            break;
        case 1: //Down
            if (mirror.getYPos() - yPos <= spriteHeight / 2 + mirror.getSpriteHeigth() / 2 + 20) {
                if (abs(mirror.getXPos() - xPos) <= 20) {
                    xPos = mirror.getXPos();
                    yPos = mirror.getYPos() - mirror.getSpriteHeigth() / 2 - spriteHeight / 2;
                    return true;
                }
            }
            break;
        case 2: //Left
            if (xPos - mirror.getXPos() <= spriteWidth / 2 + mirror.getSpriteWidth() / 2 + 20) {
                if (abs(mirror.getYPos() - yPos) <= 20) {
                    xPos = mirror.getXPos() + mirror.getSpriteWidth() / 2 + spriteWidth / 2;
                    yPos = mirror.getYPos();
                    return true;
                }
            }
            break;
        case 3: //Up
            if (yPos - mirror.getYPos() <= spriteWidth / 2 + mirror.getSpriteWidth() / 2 + 20) {
                if (abs(mirror.getXPos() - xPos) <= 20) {
                    xPos = mirror.getXPos();
                    yPos = mirror.getYPos() + spriteHeight / 2 + mirror.getSpriteHeigth() / 2;
                    return true;
                }
            }
            break;
        default:
            std::cout << "Major system error ... " << std::endl;
            return false;
    }
    return false;
}
