#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

Animation::Animation(const std::string &textureFileName, ushort spriteWidth, ushort spriteHeight) {
    if(!texture.loadFromFile(textureFileName)){
        std::cout << "Couldn't open texture file" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,spriteWidth,spriteHeight));
    sprite.setScale(4,4);
    sprite.move(100,100);
}

void Animation::Animate(float time, ushort speed) {
    currentFrame += 0.005 * time;
    if (currentFrame > 8) {
        currentFrame -= 8;
    }
    sprite.setTextureRect(sf::IntRect(24 * (int)currentFrame,0,24,15));
    sprite.move(0, -speed * time);

}
