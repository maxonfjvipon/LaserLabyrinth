#include "MainHero.h"
#include <iostream>

MainHero::MainHero() {
    std::ifstream mainHeroInputFile("files/constructMainHero.txt");
    std::string textureFileName;
    mainHeroInputFile >> xPos >> yPos; // input position
    mainHeroInputFile >> textureFileName;
    textureFileName += ".png";
    animation = Animation(textureFileName,spriteWidth,spriteHeight);
}

void MainHero::move(sf::Event &event, float time, sf::RenderWindow &window) {
    switch (event.key.code) {
        case sf::Keyboard::W:
            this->yPos -= speed;
            std::cout << yPos << " ";
            animation.animate(time, speed);
            window.draw(animation.sprite);
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
