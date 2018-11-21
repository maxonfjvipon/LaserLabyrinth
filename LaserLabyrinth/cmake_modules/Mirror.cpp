#include "Mirror.h"
#include <fstream>


Mirror::Mirror(std::ifstream &fin) {
    fin >> xPos >> yPos >> rotateAngle;
    std::string textureFileName;
    fin >> textureFileName;
    picture = Picture();
    picture.set(textureFileName,spriteWidth,spriteHeight,xPos,yPos,rotateAngle);
}
