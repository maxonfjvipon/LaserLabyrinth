#include "Level.h"
#include "MainHero.h"
#include <fstream>
#include <iostream>
#include <cmath>

template<class T>
void setNewImage(T &object, const std::string &fileName, ushort rotateAngle) {
    object.image.setParameters(fileName, 32, 32);
    object.image.set(object.transform.x, object.transform.y, rotateAngle);
}

void Level::set(const std::string &levelFileName, ushort level){

    currentLevel = level;

    rays.clear();
    gameObjects.clear();
    isPause = false;
    isDoorOpen = false;

    font.loadFromFile("fonts/pixel.ttf");
    doorText.setFont(font);
    doorText.setCharacterSize(20);
    doorText.setString("");
    doorText.setFillColor(sf::Color::White);
    doorText.setOutlineColor(sf::Color::Black);
    doorText.setOrigin(doorText.getLocalBounds().width / 2, doorText.getLocalBounds().height / 2);

    std::ifstream fin(levelFileName);

    map.setParametersFromFile(fin);
    int mapX, mapY;
    ushort mapAngle;
    fin >> mapX >> mapY >> mapAngle;
    map.set(mapX, mapY, mapAngle);

    hero.set(fin);

    fin >> mirrorsQuantity;

    for (short i = 0; i < mirrorsQuantity; i++) {
        gameObjects.push_back(new Mirror());
        gameObjects[i]->set(fin);
    }

    uint otherObjectsCount;
    fin >> otherObjectsCount;

    for (short i = 0; i < otherObjectsCount; i++) {
        gameObjects.push_back(new Object());
        gameObjects[i + mirrorsQuantity]->set(fin);
    }

    //todo другие объекты

    auto *laserCannon = new LaserCannon();
    laserCannon->set(fin);
    gameObjects.push_back(laserCannon);
    laserCannonIndex = static_cast<ushort>(gameObjects.size() - 1);
    ray.set(laserCannon->transform.x, laserCannon->transform.y, laserCannon->transform.rotateAngle);
    setRays();
    fin.close();

}

void Level::actions() {
    if (wasButtonPressed()) {
        setRays();
        auto *door = (Object *) gameObjects[laserCannonIndex - 1];
        if (sqrt(pow((hero.transform.x - door->transform.x), 2)
                 + pow((hero.transform.y - door->transform.y), 2)) > distanceForInteract) {
            doorText.setString("");
        }
        return;
    }
    noActions();
}

void Level::setRays() {
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
        if (!rayCollider(_ray, static_cast<int>(_ray.x + 10000 * cos(_ray.angle)),
                         static_cast<int>(_ray.y + 10000 * sin(_ray.angle)))) {
            rays.push_back(_ray);
        }
    }
}

void Level::draw(sf::RenderWindow &window) {
    window.draw(map.sprite);
    for (auto &gameObject : gameObjects) {
        window.draw(gameObject->image.sprite);
        gameObject->canReflect = false;
    }
    for (auto &ray : rays) {
        window.draw(ray.line);
    }
    window.draw(hero.image.sprite);
    doorText.setPosition(hero.transform.x - doorText.getLocalBounds().width / 2,
                         hero.transform.y - 70);
    window.draw(doorText);
}

bool Level::wasButtonPressed() {
    if(!isPause) {
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            F();
            return true;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        isPause = !isPause;
        return true;
    }
    return false;
}

// no actions
void Level::noActions() {
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

void Level::WASD(ushort direction) {
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
void Level::R() {
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

void Level::E() {
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
            Mirror *mirror;
            for (auto i = 0; i < mirrorsQuantity; i++) {
                mirror = (Mirror *) gameObjects[i];
                if (isMirrorOnHerosWay(mirror)) {
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

void Level::F() {
    auto *door = (Object *) gameObjects[laserCannonIndex - 1];
    if (sqrt(pow((hero.transform.x - door->transform.x), 2)
             + pow((hero.transform.y - door->transform.y), 2)) <= distanceForInteract) {
        if (!isDoorOpen) {
            doorText.setString("Door is closed");
        } else {
            currentLevel++;
        }
    }
}

bool Level::isMirrorOnHerosWay(Mirror *mirror) {
    if (sqrt(pow((hero.transform.x - mirror->transform.x), 2)
             + pow((hero.transform.y - mirror->transform.y), 2)) <= distanceForInteract) {
        switch (hero.currentDirection) {
            case 0:
                if (mirror->transform.x > hero.transform.x) {
                    hero.transform.x = mirror->transform.x - distanceForInteract
                                       + 10 * mirror->image.scale;
                    hero.transform.y = mirror->transform.y;
                    return true;
                }
                break;
            case 1:
                if (mirror->transform.y > hero.transform.y) {
                    hero.transform.y = mirror->transform.y - distanceForInteract
                                       + 10 * mirror->image.scale;
                    hero.transform.x = mirror->transform.x;
                    return true;
                }
                break;
            case 2:
                if (mirror->transform.x < hero.transform.x) {
                    hero.transform.x = mirror->transform.x + distanceForInteract
                                       - 10 * mirror->image.scale;
                    hero.transform.y = mirror->transform.y;
                    return true;
                }
                break;
            case 3:
                if (mirror->transform.y < hero.transform.y) {
                    hero.transform.y = mirror->transform.y + distanceForInteract
                                       - 10 * mirror->image.scale;
                    hero.transform.x = mirror->transform.x;
                    return true;
                }
                break;
        }
    }
    return false;
}

bool Level::collider() {
    for (auto it = gameObjects.begin(); it < gameObjects.end(); it++) {
        if (hero.getRect().intersects((*it)->getRect())) {
            return true;
        }
    }

    for (uint i = 0; i < mirrorsQuantity; i++) {
        for (uint j = mirrorsQuantity; j < gameObjects.size(); j++) {
            if (gameObjects[i]->getRect().intersects(gameObjects[j]->getRect())) {
                return true;
            }
        }
    }
    return false;
}

void reflectRay(double &rayAngle, double &mirrorAngle) {
    while (mirrorAngle < 0) {
        mirrorAngle += 2 * M_PI;
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

bool Level::drawAnyRay() {

    while (ray.angle < 0) {
        ray.angle += 2 * M_PI;
    }
    short globalIndex = 0;
    std::vector<short> globalIndexes;
    ushort index;
    Line intersectPoint{};
    std::vector<Line> intersectPoints;
    std::vector<Line> tempMirrors;
    static int prevReflIndex; //номер зеркала отразившего предыдущий отрезок
    bool allow = false; //разрешение на отражение отрезка

    Mirror *currMirror;
    for (index = 0; index < mirrorsQuantity; index++) {
        currMirror = (Mirror *) gameObjects[index];
        if (!currMirror->canReflect && getIntersectionPoint(*currMirror, intersectPoint, ray)) {
            tempMirrors.push_back(currMirror->getLine());
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
            int rX = ray.x, rY = ray.y;
            ray.x = intersectPoints[prevReflIndex].x;
            ray.y = intersectPoints[prevReflIndex].y;
            _ray.set(rX, rY, ray.x, ray.y, ray.angle);
            if (rayCollider(_ray, ray.x, ray.y)) {
                return false;
            }
            currMirror = (Mirror *) gameObjects[prevReflIndex = globalIndex];
            rays.push_back(_ray);
            reflectRay(ray.angle, currMirror->getLine().angle);
            currMirror->canReflect = true;
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

template<class type>
bool Level::getIntersectionPoint(type &object, Line &intersectionPoint, Line &_ray) {
    Line intLine;
    intLine.x = ((_ray.b - object.getLine().b) / (object.getLine().k - _ray.k));
    if ((int) (_ray.angle * 180 / M_PI) % 360 == 90 ||
        (int) (_ray.angle * 180 / M_PI) % 360 == 270) {
        intLine.y = object.transform.y;
    } else {
        intLine.y = intLine.x * _ray.k + _ray.b;
    }
    intersectionPoint.x = intLine.x;
    intersectionPoint.y = intLine.y;
    return ((int) intLine.y >= object.transform.y - object.image.height / 2 * object.image.scale &&
            (int) intLine.y <= object.transform.y + object.image.height / 2 * object.image.scale &&
            (int) intLine.x <= object.transform.x + object.image.width / 2 * object.image.scale &&
            (int) intLine.x >= object.transform.x - object.image.width / 2 * object.image.scale);

}

bool Level::isDirectionCorrect(Line &ray, Line &obj) {
    return (sqrt(pow((ray.x + cos(ray.angle) - obj.x), 2)
                 + pow((ray.y + sin(ray.angle) - obj.y), 2)) <
            sqrt(pow((ray.x - obj.x), 2) + pow((ray.y - obj.y), 2)));
}

template<class type>
void Level::rayCollideWithObject(Ray &_ray, type &object, int &x, int &y) {
    Line objectLine{};
    if (getIntersectionPoint(object, objectLine, _ray)) {
        if ((int) abs(objectLine.x - _ray.x) <= (int) abs(x - _ray.x) + 10 &&
            (int) abs(objectLine.y - _ray.y) <= (int) abs(y - _ray.y) + 10) { //fixme погрешность??
            Line intersectLine = objectLine;
            objectLine.set(_ray.x, _ray.y, _ray.angle * 180 / M_PI);
            if (isDirectionCorrect(objectLine, intersectLine)) {
                x = static_cast<int>(intersectLine.x);
                y = static_cast<int>(intersectLine.y);
                ushort radius = (object.image.width >= object.image.height
                                 ? object.image.height : object.image.width) / 2 *
                                object.image.scale;
                _ray.set(_ray.x, _ray.y, intersectLine.x - radius * cos(_ray.angle),
                         intersectLine.y - radius * sin(_ray.angle), _ray.angle);
                if (object.name == "Button" && !isDoorOpen) {
                    isDoorOpen = true;
                }
                isRayCollideNow = true;
            }
        }
    }
}

bool Level::rayCollider(Ray &_ray, int mX, int mY) {
    while (_ray.angle < 0) {
        _ray.angle += 2 * M_PI;
    }
    hero.angle = static_cast<int>(_ray.angle * 180 / M_PI + 45);
    int x = mX, y = mY;
    rayCollideWithObject(_ray, hero, x, y);
    for (ushort i = mirrorsQuantity; i < gameObjects.size() - 1; i++) {
        rayCollideWithObject(_ray, *gameObjects[i], x, y);
    }
    if (isRayCollideNow) {
        rays.push_back(_ray);
        return true;
    }
    return false;
}