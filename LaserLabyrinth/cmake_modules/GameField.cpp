#include "GameField.h"
#include "MainHero.h"
#include <fstream>
#include <iostream>
#include <cmath>

template<class T>
void setNewImage(T &object, const std::string &fileName, ushort rotateAngle) {
    object.image.setParameters(fileName, 32, 32);
    object.image.set(object.transform.x, object.transform.y, rotateAngle);
}

GameField::GameField() {

    std::ifstream fin("files/constructMirrors.txt");
    fin >> mirrorsQuantity;
    for (short i = 0; i < mirrorsQuantity; i++) {
        gameObjects.push_back(new Mirror());
        gameObjects[i]->set(fin);
    }
    //todo другие объекты
    gameObjects.push_back(new LaserCannon());
    laserCannonIndex = gameObjects.size() - 1;
    gameObjects[laserCannonIndex]->set(fin);
    ray.set(gameObjects[laserCannonIndex]->transform.x, gameObjects[laserCannonIndex]->transform.y,
            gameObjects[laserCannonIndex]->transform.rotateAngle);
    fin.close();

    view.setCenter(hero.transform.x, hero.transform.y);
    //todo map????

}

void GameField::draw(sf::RenderWindow &window) {
    window.draw(hero.image.sprite);
    for (auto &gameObject : gameObjects) {
        window.draw(gameObject->image.sprite);
    }
    for (auto &ray : rays) {
        window.draw(ray.line);
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
                    if (collider()) {
                        hero.transform.x -= hero.walkSpeed;
                    }
                    break;
                case 1:
                    hero.transform.y += hero.walkSpeed;
                    if (collider()) {
                        hero.transform.y -= hero.walkSpeed;
                    }
                    break;
                case 2:
                    hero.transform.x -= hero.walkSpeed;
                    if (collider()) {
                        hero.transform.x += hero.walkSpeed;
                    }
                    break;
                default:
                    hero.transform.y -= hero.walkSpeed;
                    if (collider()) {
                        hero.transform.y += hero.walkSpeed;
                    }
                    break;
            }
            hero.image.animate(hero.transform.x, hero.transform.y, direction,
                               hero.currentDirection, true);
            break;
        case RotateMirror:
            if (hero.isStaying) {
                hero.isStaying = false;
                setNewImage(hero, "images/sprHeroRotateMirror.png", 1000);
            }
            switch (direction) {
                case 0:
                    gameObjects[hero.mirrorIndex]->rotate(1);
                    break;
                case 2:
                    gameObjects[hero.mirrorIndex]->rotate(-1);
                    break;
            }
            hero.image.animate(hero.transform.x, hero.transform.y, direction,
                               hero.currentDirection, false);
            break;
        case PushMirror:
            if (hero.isStaying) {
                hero.isStaying = false;
                setNewImage(hero, "images/sprHeroPushMirror.png", 1000);
            }
            switch (direction) {
                case 0:
                    hero.transform.x += hero.pushSpeed;
                    gameObjects[hero.mirrorIndex]->moveByX(hero.pushSpeed);
                    if (collider()) {
                        hero.transform.x -= hero.pushSpeed;
                        gameObjects[hero.mirrorIndex]->moveByX(-hero.pushSpeed);
                    }
                    gameObjects[hero.mirrorIndex]->image.sprite.setPosition(
                            gameObjects[hero.mirrorIndex]->transform.x,
                            gameObjects[hero.mirrorIndex]->transform.y);
                    break;
                case 1:
                    hero.transform.y += hero.pushSpeed;
                    gameObjects[hero.mirrorIndex]->moveByY(hero.pushSpeed);
                    if (collider()) {
                        hero.transform.y -= hero.pushSpeed;
                        gameObjects[hero.mirrorIndex]->moveByY(-hero.pushSpeed);
                    }
                    gameObjects[hero.mirrorIndex]->image.sprite.setPosition(
                            gameObjects[hero.mirrorIndex]->transform.x,
                            gameObjects[hero.mirrorIndex]->transform.y);
                    break;
                case 2:
                    hero.transform.x -= hero.pushSpeed;
                    gameObjects[hero.mirrorIndex]->moveByX(-hero.pushSpeed);
                    if (collider()) {
                        hero.transform.x += hero.pushSpeed;
                        gameObjects[hero.mirrorIndex]->moveByX(hero.pushSpeed);
                    }
                    gameObjects[hero.mirrorIndex]->image.sprite.setPosition(
                            gameObjects[hero.mirrorIndex]->transform.x,
                            gameObjects[hero.mirrorIndex]->transform.y);
                    break;
                case 3:
                    hero.transform.y -= hero.pushSpeed;
                    gameObjects[hero.mirrorIndex]->moveByY(-hero.pushSpeed);
                    if (collider()) {
                        hero.transform.y += hero.pushSpeed;
                        gameObjects[hero.mirrorIndex]->moveByY(hero.pushSpeed);
                    }
                    gameObjects[hero.mirrorIndex]->image.sprite.setPosition(
                            gameObjects[hero.mirrorIndex]->transform.x,
                            gameObjects[hero.mirrorIndex]->transform.y);
                    break;
            }
            hero.image.animate(hero.transform.x, hero.transform.y, direction,
                               hero.currentDirection, false);
            break;
    }
}


// R button
void GameField::R() {
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
            for (auto i = 0; i < gameObjects.size(); i++) {
                if (isMirrorOnHerosWay(*(gameObjects[i]))) {
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
            for (auto i = 0; i < gameObjects.size(); i++) {
                if (isMirrorOnHerosWay(*(gameObjects[i]))) {
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
bool GameField::isMirrorOnHerosWay(GameObject &gameObject) {
    if (gameObject.name == "Mirror") {
        switch (hero.currentDirection) {
            case 0: //Hero -> Mirror
                if (gameObject.transform.x - gameObject.image.width / 2 * gameObject.image.scale
                    - hero.transform.x + hero.image.width / 2 * hero.image.scale <=
                    distanceForInteract) {
                    if (abs(gameObject.transform.y - hero.transform.y) <=
                        distanceForInteract / 2) {
                        hero.transform.x = gameObject.transform.x - distanceForInteract
                                           + 10 * gameObject.image.scale;
                        hero.transform.y = gameObject.transform.y;
                        return true;
                    }
                }

                break;
            case 2: // Mirror <- Hero
                if (hero.transform.x - hero.image.width / 2 * hero.image.scale
                    - gameObject.transform.x +
                    gameObject.image.width / 2 * gameObject.image.scale <=
                    distanceForInteract) {
                    if (abs(gameObject.transform.y - hero.transform.y) <=
                        distanceForInteract / 2) {
                        hero.transform.x = gameObject.transform.x + distanceForInteract
                                           - 10 * gameObject.image.scale;
                        hero.transform.y = gameObject.transform.y;
                        return true;
                    }
                }
                break;
                //Hero
                //Mirror
            case 1:
                if (gameObject.transform.y -
                    gameObject.image.height / 2 * gameObject.image.scale
                    - hero.transform.y + hero.image.height / 2 * hero.image.scale <=
                    distanceForInteract) {
                    if (abs(gameObject.transform.x - hero.transform.x) <=
                        distanceForInteract / 2) {
                        hero.transform.y = gameObject.transform.y - distanceForInteract
                                           + 10 * gameObject.image.scale;
                        hero.transform.x = gameObject.transform.x;
                        return true;
                    }
                }
                break;
                //Mirror
                //Hero
            case 3:
                if (hero.transform.x - hero.image.height / 2 * hero.image.scale
                    - gameObject.transform.y +
                    gameObject.image.height / 2 * gameObject.image.scale <=
                    distanceForInteract) {
                    if (abs(gameObject.transform.x - hero.transform.x) <=
                        distanceForInteract / 2) {
                        hero.transform.y = gameObject.transform.y + distanceForInteract
                                           - 10 * gameObject.image.scale;
                        hero.transform.x = gameObject.transform.x;
                        return true;
                    }
                }
                break;
        }
    }
    return false;
}

bool GameField::collider() {
    for (auto it = gameObjects.begin(); it < gameObjects.end(); it++) {
        if (hero.getRect().intersects((*it)->getRect())) {
            return true;
        }
        for (auto jt = it + 1; jt < gameObjects.end(); jt++) {
            if ((*it)->getRect().intersects((*jt)->getRect())) {
                return true;
            }
        }
    }
    return false;
}

void reflectRay(double &rayAngle, double &mirrorAngle) {
    rayAngle = -rayAngle;
    mirrorAngle = -mirrorAngle;
    if (mirrorAngle >= 0 && mirrorAngle <= M_PI_2) {
        rayAngle = (2 * M_PI - rayAngle * 2 * mirrorAngle);
    } else if (mirrorAngle >= M_PI_2 && mirrorAngle <= M_PI) {
        rayAngle = (-rayAngle - 2 * (M_PI - mirrorAngle));
    } else {
        std::cout << "Invalid angles range" << std::endl;
        return;
    }
    rayAngle = -rayAngle;
}

void GameField::drawAnyRay() {

    short globalIndex;
    std::vector<short> globalIndexes;
    short index;
    Line mirror{};
    std::vector<Line> tempMirrors;
    int prevReflIndex; //номер зеркала отразившего предыдущий отрезок
    bool allow = false; //разрешение на отражение отрезка

    for (index = 0; index < mirrorsQuantity; index++) {
        mirror = gameObjects[index]->getLine();
        if (!gameObjects[index]->canReflect && getIntersectionPoint(index, mirror)) {
            tempMirrors.push_back(mirror);
            globalIndexes.push_back(index);
        }
    }

    if (!tempMirrors.empty()) {

        double d;
        gameObjects[prevReflIndex]->canReflect = false;
        prevReflIndex = index = 0;

        for (double delta = fabs(tempMirrors[prevReflIndex].x - ray.x);
             index < tempMirrors.size(); index++) {
            d = fabs(tempMirrors[index].x - ray.x);
            if (d <= delta && isDirectionCorrect(tempMirrors[index])) {
                globalIndex = globalIndexes[index];
                delta = d;
                prevReflIndex = index;
                allow = true;
            }
        }
        if (allow) {
            auto _ray = Ray();
            _ray.set(ray.x, ray.y, ray.x = tempMirrors[prevReflIndex].x,
                     ray.y = tempMirrors[prevReflIndex].y, ray.angle);
            rays.push_back(_ray);
            reflectRay(ray.angle, gameObjects[prevReflIndex = globalIndex]->getLine().angle);
            gameObjects[prevReflIndex]->canReflect = true;
            ray.k = tan(ray.angle);
            ray.b = ray.y - ray.k * ray.x;

        } else {
            std::cout << "не отражает ни одно зекало" << std::endl;
        }
    } else {
        std::cout << "cant reflect ray" << std::endl;
    }

}

bool GameField::getIntersectionPoint(ushort index, Line &mirror) {
    mirror.x = (ray.b - gameObjects[index]->getLine().b)
               / (gameObjects[index]->getLine().k - ray.k);
    mirror.y = mirror.x * ray.k + ray.b;
    return (mirror.y <= gameObjects[index]->getYBelow() &&
            mirror.y >= gameObjects[index]->getYAbove());

}

bool GameField::isDirectionCorrect(Line &mirror) {
    return (sqrt(pow((ray.x + cos(ray.angle) - mirror.x), 2)
                 + pow((ray.y + sin(ray.angle) - mirror.y), 2)) <
            sqrt(pow((ray.x - mirror.x), 2) + pow((ray.x - mirror.x), 2)));
}
