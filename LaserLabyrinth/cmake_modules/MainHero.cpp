#include "MainHero.h"
#include <iostream>

MainHero::MainHero() {
    std::ifstream mainHeroInputFile("files/constructMainHero.txt");
    std::string textureFileName;
    mainHeroInputFile >> xPos >> yPos; // input position
    mainHeroInputFile >> textureFileName;
    textureFileName += ".png";
    sf::Texture heroTexture;
    heroTexture.loadFromFile(textureFileName);
    heroSprite.setTexture(heroTexture);
}

void MainHero::move(sf::Event &event) {
    switch (event.key.code) {
        case sf::Keyboard::W:
            this->yPos -= speed;
            break;
        case sf::Keyboard::S:
            this->yPos += speed;
            break;
        case sf::Keyboard::A:
            this->xPos -= speed;
            break;
        case sf::Keyboard::D:
            this->xPos += speed;
    }
}

void MainHero::draw(sf::RenderWindow &window) {
    heroSprite.setTextureRect(sf::IntRect(0, 0, spriteWidth, spriteHeight)); //fixme
    heroSprite.setPosition(xPos + spriteWidth / 2, yPos + spriteHeight / 2);
    window.draw(heroSprite);
}
