#include "Sound.h"

void Sound::set(std::ifstream &fin, ushort volume) {
    std::string soundFileName;
    fin >> soundFileName;
    soundBuffer.loadFromFile(soundFileName);
    sound.setBuffer(soundBuffer);
    sound.setVolume(volume);
}

void Sound::setArrowsSound(ushort volume) {
    soundBuffer.loadFromFile("music/beep.wav"); //fixme
    sound.setBuffer(soundBuffer);
    sound.setVolume(volume);
}