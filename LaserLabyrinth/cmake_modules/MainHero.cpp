#include "MainHero.h"
#include <iostream>

MainHero::MainHero() {
    std::ifstream mainHeroInputFile("files/constructMainHero.txt");
    std::string textureFileName;
//    mainHeroInputFile >> xPos >> yPos; // input position
//    mainHeroInputFile >> textureFileName;
    xPos = yPos = 100;
    textureFileName = "images/heroWalkForward.png";
    std::cout << textureFileName;
    animation = Animation(textureFileName,spriteWidth,spriteHeight);
}

void MainHero::move(sf::Event &event, float time) {
    switch (event.key.code) {
        case sf::Keyboard::W:
            this->yPos -= speed;
            animation.animate(time);
            break;
        case sf::Keyboard::S:
            this->yPos += speed;
            break;
        case sf::Keyboard::A:
            this->xPos -= speed;
            break;
        case sf::Keyboard::D:
            this->xPos += speed;
            break;
    }
}
