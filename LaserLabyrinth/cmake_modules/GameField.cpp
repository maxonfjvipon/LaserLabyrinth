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

    LaserCannon *laserCannon = new LaserCannon();
    laserCannon->set(fin);
    gameObjects.push_back(laserCannon);
    laserCannonIndex = static_cast<ushort>(gameObjects.size() - 1);
    ray.set(laserCannon->transform.x, laserCannon->transform.y, laserCannon->transform.rotateAngle);

    fin.close();

    view.setCenter(hero.transform.x, hero.transform.y);
    //todo map????

    delete laserCannon;

}

void GameField::actions(sf::Event &event) {
    if (wasButtonPressed(event)) {
        view.setCenter(hero.transform.x, hero.transform.y);
        rays.clear();
        auto *laserCannon = gameObjects[laserCannonIndex];
        isRayCollideNow = false;
        ray.set(laserCannon->transform.x, laserCannon->transform.y,
                laserCannon->transform.rotateAngle);
        do {
        } while (drawAnyRay());
        if (!isRayCollideNow) {
            auto _ray = Ray();
            _ray.set(static_cast<int>(ray.x), static_cast<int>(ray.y), ray.angle, 10000);
            if (!rayCollider(_ray, static_cast<int>(_ray.x - 10000 * cos(_ray.angle)),
                             static_cast<int>(_ray.y - 10000 * sin(_ray.angle)))) {
                rays.push_back(_ray);
            }
        }
        return;
    }
    noActions();
    view.setCenter(hero.transform.x, hero.transform.y);
}

void GameField::draw(sf::RenderWindow &window) {
    window.draw(hero.image.sprite);
    for (auto &gameObject : gameObjects) {
        window.draw(gameObject->image.sprite);
        gameObject->canReflect = false;
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
        case RotateMirror: {
            if (hero.isStaying) {
                hero.isStaying = false;
                setNewImage(hero, "images/sprHeroRotateMirror.png", 1000);
            }
            auto *mirror = (Mirror *) gameObjects[hero.mirrorIndex];
            switch (direction) {
                case 0:
                    mirror->rotate(1);
                    break;
                case 2:
                    mirror->rotate(-1);
                    break;
            }
            hero.image.animate(hero.transform.x, hero.transform.y, direction,
                               hero.currentDirection, false);
            delete mirror;
        }
            break;
        case PushMirror: {
            if (hero.isStaying) {
                hero.isStaying = false;
                setNewImage(hero, "images/sprHeroPushMirror.png", 1000);
            }
            auto *mirror = (Mirror *) gameObjects[hero.mirrorIndex];
            switch (direction) {
                case 0:
                    hero.transform.x += hero.pushSpeed;
                    mirror->moveByX(hero.pushSpeed);
                    if (collider()) {
                        hero.transform.x -= hero.pushSpeed;
                        mirror->moveByX(-hero.pushSpeed);
                    }
                    break;
                case 1:
                    hero.transform.y += hero.pushSpeed;
                    mirror->moveByY(hero.pushSpeed);
                    if (collider()) {
                        hero.transform.y -= hero.pushSpeed;
                        mirror->moveByY(-hero.pushSpeed);
                    }
                    break;
                case 2:
                    hero.transform.x -= hero.pushSpeed;
                    mirror->moveByX(-hero.pushSpeed);
                    if (collider()) {
                        hero.transform.x += hero.pushSpeed;
                        mirror->moveByX(hero.pushSpeed);
                    }
                    break;
                case 3:
                    hero.transform.y -= hero.pushSpeed;
                    mirror->moveByY(-hero.pushSpeed);
                    if (collider()) {
                        hero.transform.y += hero.pushSpeed;
                        mirror->moveByY(hero.pushSpeed);
                    }
                    break;
            }
            mirror->image.sprite.setPosition(mirror->transform.x, mirror->transform.y);
            hero.image.animate(hero.transform.x, hero.transform.y, direction,
                               hero.currentDirection, false);
        }
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
            Mirror *mirror;
            for (auto i = 0; i < gameObjects.size(); i++) {
                mirror = (Mirror *) gameObjects[i];
                if (isMirrorOnHerosWay(mirror)) {
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
                if (isMirrorOnHerosWay() { //fixme
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
bool GameField::isMirrorOnHerosWay(Mirror *mirror) {
    if (mirror->name == "Mirror") {
        switch (hero.currentDirection) {
            case 0: //Hero -> Mirror
                if (mirror->transform.x - mirror->image.width / 2 * mirror->image.scale
                    - hero.transform.x + hero.image.width / 2 * hero.image.scale <=
                    distanceForInteract) {
                    if (abs(mirror->transform.y - hero.transform.y) <=
                        distanceForInteract / 2) {
                        hero.transform.x = mirror->transform.x - distanceForInteract
                                           + 10 * mirror->image.scale;
                        hero.transform.y = mirror->transform.y;
                        return true;
                    }
                }

                break;
            case 2: // Mirror <- Hero
                if (hero.transform.x - hero.image.width / 2 * hero.image.scale -
                    mirror->transform.x + mirror->image.width / 2 * mirror->image.scale <=
                    distanceForInteract) {
                    if (abs(mirror->transform.y - hero.transform.y) <=
                        distanceForInteract / 2) {
                        hero.transform.x = mirror->transform.x + distanceForInteract
                                           - 10 * mirror->image.scale;
                        hero.transform.y = mirror->transform.y;
                        return true;
                    }
                }
                break;
                //Hero
                //Mirror
            case 1:
                if (mirror->transform.y -
                    mirror->image.height / 2 * mirror->image.scale
                    - hero.transform.y + hero.image.height / 2 * hero.image.scale <=
                    distanceForInteract) {
                    if (abs(mirror->transform.x - hero.transform.x) <=
                        distanceForInteract / 2) {
                        hero.transform.y = mirror->transform.y - distanceForInteract
                                           + 10 * mirror->image.scale;
                        hero.transform.x = mirror->transform.x;
                        return true;
                    }
                }
                break;
                //Mirror
                //Hero
            case 3:
                if (hero.transform.x - hero.image.height / 2 * hero.image.scale
                    - mirror->transform.y +
                    mirror->image.height / 2 * mirror->image.scale <= distanceForInteract) {
                    if (abs(mirror->transform.x - hero.transform.x) <= distanceForInteract / 2) {
                        hero.transform.y = mirror->transform.y + distanceForInteract
                                           - 10 * mirror->image.scale;
                        hero.transform.x = mirror->transform.x;
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
    while (mirrorAngle < 0) {
        mirrorAngle += M_PI;
    }
    if ((mirrorAngle >= 0 && mirrorAngle <= M_PI_2) ||
        (mirrorAngle >= M_PI && mirrorAngle <= 3 * M_PI_2)) {
        rayAngle = (2 * M_PI - rayAngle + 2 * mirrorAngle);
    } else if ((mirrorAngle >= M_PI_2 && mirrorAngle <= M_PI) ||
               (mirrorAngle >= 3 * M_PI_2 && mirrorAngle <= 2 * M_PI)) {
        rayAngle = (-rayAngle - 2 * (M_PI - mirrorAngle));
    } else {
        std::cout << "Invalid angles range" << std::endl;
        return;
    }
}

bool GameField::drawAnyRay() {

    short globalIndex = 0;
    std::vector<short> globalIndexes;
    ushort index;
    Line mirror {}, intersectPoint {};
    std::vector<Line> intersectPoints;
    std::vector<Line> tempMirrors;
    static int prevReflIndex; //номер зеркала отразившего предыдущий отрезок
    bool allow = false; //разрешение на отражение отрезка

    Mirror *currMirror;
    for (index = 0; index < mirrorsQuantity; index++) {
        currMirror = (Mirror*)gameObjects[index];
        mirror = currMirror->getLine();
        if (!currMirror->canReflect && getIntersectionPoint(index, mirror,
                                                                    intersectPoint)) {
            tempMirrors.push_back(mirror);
            intersectPoints.push_back(intersectPoint);
            globalIndexes.push_back(index);
        }
    }

    if (!tempMirrors.empty()) {

        double d = 0;
        gameObjects[prevReflIndex]->canReflect = false;
        prevReflIndex = index = 0;

        for (double delta = fabs(tempMirrors[prevReflIndex].x - ray.x);
             index < tempMirrors.size(); index++) {
            d = static_cast<uint>(abs(tempMirrors[index].x - ray.x));
            if (d <= delta && isDirectionCorrect(ray, tempMirrors[index])) {
                globalIndex = globalIndexes[index];
                delta = d;
                prevReflIndex = index;
                allow = true;
            }
        }
        if (allow) {
            auto _ray = Ray();
            _ray.set(static_cast<int>(ray.x), static_cast<int>(ray.y),
                     static_cast<int>(ray.x = intersectPoints[prevReflIndex].x),
                     static_cast<int>(ray.y = intersectPoints[prevReflIndex].y), ray.angle);
            if (rayCollider(_ray, intersectPoints[prevReflIndex].x,
                            intersectPoints[prevReflIndex].y)) {
                return false;
            }
            rays.push_back(_ray);
            reflectRay(ray.angle, gameObjects[prevReflIndex = globalIndex]->getLine().angle);
            gameObjects[prevReflIndex]->canReflect = true;
            ray.k = tan(ray.angle);
            ray.b = ray.y - ray.k * ray.x;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }

}


bool GameField::getIntersectionPoint(ushort index, Line mirror, Line &intersectionPoint) {
    mirror.x = ((ray.b - gameObjects[index]->getLine().b)
                / (gameObjects[index]->getLine().k - ray.k));
    mirror.y = mirror.x * ray.k + ray.b;
    intersectionPoint.x = mirror.x;
    intersectionPoint.y = mirror.y;
    return ((int) mirror.y >= gameObjects[index]->getYBelow() &&
            (int) mirror.y <= gameObjects[index]->getYAbove() &&
            (int) mirror.x <= gameObjects[index]->getXRigth() &&
            (int) mirror.x >= gameObjects[index]->getXLeft());

}

bool GameField::isDirectionCorrect(Line &ray, Line &obj) {
    return (sqrt(pow((ray.x + cos(ray.angle) - obj.x), 2)
                 + pow((ray.y + sin(ray.angle) - obj.y), 2)) <
            sqrt(pow((ray.x - obj.x), 2) + pow((ray.y - obj.y), 2)));
}


template<class type>
bool GameField::isRayCollideWithObject(Ray &_ray, type &object, int mX, int mY) {
    Line objectLine {};
    objectLine.x = ((_ray.b - object.getLine().b) / (object.getLine().k - _ray.k));
    objectLine.y = objectLine.x * _ray.k + _ray.b;
    if ((int) objectLine.y >= object.transform.y - object.image.height / 2 * object.image.scale &&
        (int) objectLine.y <= object.transform.y + object.image.height / 2 * object.image.scale &&
        (int) objectLine.x <= object.transform.x + object.image.width / 2 * object.image.scale &&
        (int) objectLine.x >= object.transform.x - object.image.width / 2 * object.image.scale) {
        if (abs(object.transform.x - _ray.x) < abs(mX - _ray.x) &&
            abs(object.transform.y - _ray.y) < abs(mY - _ray.y)) {
            objectLine.set(_ray.x, _ray.y, _ray.angle * 180 / M_PI);
            if (isDirectionCorrect(objectLine, object.getLine())) {
                ushort radius = object.image.width / 2 * object.image.scale;
                _ray.set(_ray.x, _ray.y, object.transform.x - radius * cos(_ray.angle),
                         object.transform.y - radius * sin(_ray.angle), _ray.angle);
                rays.push_back(_ray);
                isRayCollideNow = true;
                return true;
            }
        }
    }
    return false;
}

bool GameField::rayCollider(Ray &_ray, int mX, int mY) {
    if (isRayCollideWithObject(_ray, hero, mX, mY)) {
        return true;
    }
    for (ushort i = mirrorsQuantity; i < gameObjects.size() - 1; i++) {
        if (isRayCollideWithObject(_ray, *gameObjects[i], mX, mY)) {
            return true;
        }
    }
    return false;
}
