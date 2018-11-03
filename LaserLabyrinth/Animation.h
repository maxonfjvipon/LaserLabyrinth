#ifndef LASERLABYRINTH_ANIMATION_H
#define LASERLABYRINTH_ANIMATION_H


#include <SFML/Graphics.hpp>

class Animation {

    void Animate(float time);

public:

    float currentFrame = 0; // хранит текущий кадр
    sf::Sprite sprite;

    Animation() = default;

    Animation(const std::string &textureFileName, ushort spriteWidth, ushort spriteHeight);

    void animate(float time){
        Animate(time);
    }

};


#endif //LASERLABYRINTH_ANIMATION_H
