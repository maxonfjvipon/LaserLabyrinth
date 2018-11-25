#include "GameField.h"
#include <fstream>
#include <iostream>

template<class T>
void setNewImage(T &object, const std::string &fileName, ushort rotateAngle) {
    object.image.setParameters(fileName, 32, 32);
    object.image.set(object.transform.x, object.transform.y, rotateAngle);
}

GameField::GameField() {

    std::ifstream fin("files/constructMirrors.txt");
    fin >> mirrorsQuantity;
    mirrors.resize(mirrorsQuantity);
    for (auto &mirror : mirrors) {
        mirror.set(fin);
    }
    fin.close();

}

void GameField::draw(sf::RenderWindow &window) {
    window.draw(hero.image.sprite);
    for (auto &mirror : mirrors) {
        window.draw(mirror.image.sprite);
    }
}

bool GameField::wasButtonPressed(sf::Event &event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        WASD(2);
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        WASD(0);
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        WASD(1);
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        WASD(3);
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        R();
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        E();
        return true;
    }
    return false;
}

// no actions
void GameField::noActions() {
    if (!hero.isStaying) {
        hero.isStaying = true;
        switch (hero.mode) {
            case Walk:
                setNewImage(hero, "images/heroStays.png",
                            static_cast<ushort>(hero.currentDirection * 90));
                break;
            case RotateMirror:
                setNewImage(hero, "images/heroRotateStays.png",
                            static_cast<ushort>(hero.currentDirection * 90));
                break;
            case PushMirror:
                setNewImage(hero, "images/heroPushStays.png",
                            static_cast<ushort>(hero.currentDirection * 90));
                break;
        }
    }
}

void GameField::WASD(ushort direction) {
    switch (hero.mode) {
        case Walk:
            if (hero.isStaying) {
                hero.isStaying = false;
                setNewImage(hero, "images/sprHeroWalk.png", 1000);
            }
            switch (direction) {
                case 0:
                    hero.transform.x += hero.walkSpeed;
                    for (auto &mirror : mirrors) {
                        if (collide(hero, mirror)) {
                            hero.transform.x -= hero.walkSpeed;
                            break;
                        }
                    }
                    break;
                case 1:
                    hero.transform.y += hero.walkSpeed;
                    for (auto &mirror : mirrors) {
                        if (collide(hero, mirror)) {
                            hero.transform.y -= hero.walkSpeed;
                            break;
                        }
                    }
                    break;
                case 2:
                    hero.transform.x -= hero.walkSpeed;
                    for (auto &mirror : mirrors) {
                        if (collide(hero, mirror)) {
                            hero.transform.x += hero.walkSpeed;
                            break;
                        }
                    }
                    break;
                default:
                    hero.transform.y -= hero.walkSpeed;
                    for (auto &mirror : mirrors) {
                        if (collide(hero, mirror)) {
                            hero.transform.y += hero.walkSpeed;
                            break;
                        }
                    }
                    break;
            }
            std::cout << hero.transform.x << ":" << hero.transform.y << std::endl;
            hero.image.animate(hero.transform.x, hero.transform.y, direction, hero.currentDirection,
                               true);
            break;
        case RotateMirror:
            if (hero.isStaying) {
                hero.isStaying = false;
                setNewImage(hero, "images/sprHeroRotateMirror.png", 1000);
            }
            switch (direction) {
                case 0:
                    mirrors[hero.mirrorIndex].rotate(-1);
                    break;
                case 2:
                    mirrors[hero.mirrorIndex].rotate(1);
                    break;
            }
            hero.image.animate(hero.transform.x, hero.transform.y, direction, hero.currentDirection,
                               false);
            break;
        case PushMirror:
            if (hero.isStaying) {
                hero.isStaying = false;
                setNewImage(hero, "images/sprHeroPushMirror.png", 1000);
            }
            switch (direction) {
                case 0:
                    hero.transform.x += hero.walkSpeed;
                    mirrors[hero.mirrorIndex].transform.x += hero.walkSpeed;
                    mirrors[hero.mirrorIndex].image.sprite.setPosition(
                            mirrors[hero.mirrorIndex].transform.x,
                            mirrors[hero.mirrorIndex].transform.y);
                    break;
                case 1:
                    hero.transform.y += hero.walkSpeed;
                    mirrors[hero.mirrorIndex].transform.y += hero.walkSpeed;
                    mirrors[hero.mirrorIndex].image.sprite.setPosition(
                            mirrors[hero.mirrorIndex].transform.x,
                            mirrors[hero.mirrorIndex].transform.y);
                    break;
                case 2:
                    hero.transform.x -= hero.walkSpeed;
                    mirrors[hero.mirrorIndex].transform.x -= hero.walkSpeed;
                    mirrors[hero.mirrorIndex].image.sprite.setPosition(
                            mirrors[hero.mirrorIndex].transform.x,
                            mirrors[hero.mirrorIndex].transform.y);
                    break;
                case 3:
                    hero.transform.y -= hero.walkSpeed;
                    mirrors[hero.mirrorIndex].transform.y -= hero.walkSpeed;
                    mirrors[hero.mirrorIndex].image.sprite.setPosition(
                            mirrors[hero.mirrorIndex].transform.x,
                            mirrors[hero.mirrorIndex].transform.y);
                    break;
            }
            hero.image.animate(hero.transform.x, hero.transform.y, direction, hero.currentDirection,
                               false);
            break;
    }
}

// R button
void GameField::R() {
    std::cout << "R pressed" << std::endl;
    switch (hero.mode) {
        case RotateMirror:
            hero.mode = Walk;
            hero.isStaying = true;
            hero.mirrorIndex = -1;
            return;
        case PushMirror:
            hero.mode = RotateMirror;
            hero.isStaying = true;
            return;
        case Walk:
            for (auto i = 0; i < mirrors.size(); i++) {
                if (isMirrorOnHerosWay(mirrors[i])) {
                    hero.mirrorIndex = i;
                    break;
                }
            }
            if (hero.mirrorIndex == -1) {
                return;
            }
            hero.mode = RotateMirror;
            setNewImage(hero, "images/heroRotateStays.png",
                        static_cast<ushort>(hero.currentDirection * 90));
            hero.isStaying = true;
            break;
    }
}

void GameField::E() {
    std::cout << "E pressed" << std::endl;
    switch (hero.mode) {
        case PushMirror:
            hero.mode = Walk;
            hero.isStaying = true;
            hero.mirrorIndex = -1;
            return;
        case RotateMirror:
            hero.mode = PushMirror;
            hero.isStaying = true;
            return;
        case Walk:
            for (auto i = 0; i < mirrors.size(); i++) {
                if (isMirrorOnHerosWay(mirrors[i])) {
                    hero.mirrorIndex = i;
                    break;
                }
            }
            if (hero.mirrorIndex == -1) {
                return;
            }
            hero.mode = PushMirror;
            setNewImage(hero, "images/heroPushStays.png",
                        static_cast<ushort>(hero.currentDirection * 90));
            hero.isStaying = true;
            break;
    }
}

// fixme учесть расстояние между краем спрайта и реальной картинкой
bool GameField::isMirrorOnHerosWay(Mirror &mirror) {
    switch (hero.currentDirection) {
        case 0: //Hero -> Mirror
            if (mirror.transform.x - mirror.image.width / 2 * mirror.image.scale
                - hero.transform.x + hero.image.width / 2 * hero.image.scale <=
                distanseForInteract) {
                if (abs(mirror.transform.y - hero.transform.y) <= distanseForInteract / 2) {
                    hero.transform.x = mirror.transform.x - mirror.image.width / 2
                                                            * mirror.image.scale -
                                       hero.image.width / 2 * hero.image.scale;
                    hero.transform.y = mirror.transform.y;
                    return true;
                }
            }
            break;
        case 2: // Mirror <- Hero
            if (hero.transform.x - hero.image.width / 2 * hero.image.scale
                - mirror.transform.x + mirror.image.width / 2 * mirror.image.scale <=
                distanseForInteract) {
                if (abs(mirror.transform.y - hero.transform.y) <= distanseForInteract / 2) {
                    hero.transform.x = mirror.transform.x + mirror.image.width / 2
                                                            * mirror.image.scale +
                                       hero.image.width / 2 * hero.image.scale;
                    hero.transform.y = mirror.transform.y;
                    return true;
                }
            }
            break;
            //Hero
            //Mirror
        case 1:
            if (mirror.transform.y - mirror.image.height / 2 * mirror.image.scale
                - hero.transform.y + hero.image.height / 2 * hero.image.scale <=
                distanseForInteract) {
                if (abs(mirror.transform.x - hero.transform.x) <= distanseForInteract / 2) {
                    hero.transform.y = mirror.transform.y - mirror.image.height / 2
                                                            * mirror.image.scale
                                       - hero.image.height / 2 * hero.image.scale;
                    hero.transform.x = mirror.transform.x;
                    return true;
                }
            }
            break;
            //Mirror
            //Hero
        case 3:
            if (hero.transform.x - hero.image.height / 2 * hero.image.scale
                - mirror.transform.y + mirror.image.height / 2 * mirror.image.scale <=
                distanseForInteract) {
                if (abs(mirror.transform.x - hero.transform.x) <= distanseForInteract / 2) {
                    hero.transform.y = mirror.transform.y + mirror.image.height / 2
                                                            * mirror.image.scale
                                       + hero.image.height / 2 * hero.image.scale;
                    hero.transform.x = mirror.transform.x;
                    return true;
                }
            }
            break;

    }
    return false;
}

template<class type1, class type2>
bool GameField::collide(type1 &object1, type2 &object2) {
    if (object1.image.sprite.getGlobalBounds().intersects(object2.image.sprite.getGlobalBounds())) {
        return true;
    }
    return false;
}
