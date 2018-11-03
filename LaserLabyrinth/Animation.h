#ifndef LASERLABYRINTH_ANIMATION_H
#define LASERLABYRINTH_ANIMATION_H


#include <SFML/Graphics.hpp>

class Animation {

    void Animate(float time, ushort speed);

public:

    float currentFrame = 0; // хранит текущий кадр
    sf::Sprite sprite; //хранит спрайт

    Animation() = default;

    Animation(const std::string &textureFileName, ushort spriteWidth, ushort spriteHeight);

    void animate(float time, ushort speed) {
        Animate(time, speed);
    }

};


#endif //LASERLABYRINTH_ANIMATION_H
