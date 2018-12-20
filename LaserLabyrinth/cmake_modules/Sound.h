#ifndef LASERLABYRINTH_SOUND_H
#define LASERLABYRINTH_SOUND_H

#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>

class Sound {

    std::string soundName;
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;

public:

    Sound() = default;

    void set(std::ifstream &fin, ushort volume);

    void play() {
        sound.play();
    }

};

#endif //LASERLABYRINTH_SOUND_H
