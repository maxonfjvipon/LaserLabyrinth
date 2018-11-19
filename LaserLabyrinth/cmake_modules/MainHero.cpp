#include "MainHero.h"
#include <iostream>

MainHero::MainHero() {
    std::ifstream mainHeroInputFile("files/constructMainHero.txt");
    std::string textureFileName;
    mainHeroInputFile >> xPos >> yPos; // input position
    mainHeroInputFile >> textureFileName;
    textureFileName += ".png";
    picture = Picture();
    picture.set(textureFileName, spriteWidth, spriteHeight, xPos, yPos);
}

void MainHero::move(sf::Event &event) {
    switch (event.key.code) {
        case sf::Keyboard::W:
            this->yPos -= speed;
            picture.animate(0, -speed, spriteWidth, spriteHeight, 0);
            break;
        case sf::Keyboard::S:
            this->yPos += speed;
            picture.animate(0, speed, spriteWidth, spriteHeight, 2);
            break;
        case sf::Keyboard::A:
            this->xPos -= speed;
            picture.animate(-speed, 0, spriteWidth, spriteHeight, 3);
            break;
        case sf::Keyboard::D:
            this->xPos += speed;
            picture.animate(speed, 0, spriteWidth, spriteHeight, 1);
            break;
    }
}
