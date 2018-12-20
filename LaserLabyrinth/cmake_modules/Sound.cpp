#include "Sound.h"

void Sound::set(const std::string &soundFileName, ushort volume) {
    soundBuffer.loadFromFile(soundFileName);
    sound.setBuffer(soundBuffer);
    sound.setVolume(volume);
}
