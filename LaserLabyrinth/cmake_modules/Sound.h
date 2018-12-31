#ifndef LASERLABYRINTH_SOUND_H
#define LASERLABYRINTH_SOUND_H

#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>

class Sound {

    sf::SoundBuffer soundBuffer;
    sf::Sound sound;

public:

    Sound() = default;

    void set(std::ifstream &fin, ushort volume);

    void setArrowsSound(ushort volume);

    void play() {
        sound.play();
    }

    void setVolume(ushort volume) {
        sound.setVolume(volume);
    }

};

#endif //LASERLABYRINTH_SOUND_H
