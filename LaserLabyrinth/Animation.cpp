#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

Animation::Animation(const std::string &textureFileName, ushort spriteWidth, ushort spriteHeight) {
    sf::Texture texture;
    if(texture.loadFromFile("images/heroWalkForward.png")){
        std::cout << "invalid" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,spriteWidth,spriteHeight));
}

void Animation::Animate(float time) {
    currentFrame += 0.005 * time;
    if (currentFrame > 8) {
        currentFrame -= 8;
    }
    sprite.setTextureRect(sf::IntRect(24 * (int)currentFrame,0,24,15));
    sprite.move(0, static_cast<float>(-0.1 * time));

}
