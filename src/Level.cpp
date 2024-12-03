#include "../include/Level.h"
#include "../include/Utils.h"

int Level::levelNum = 1;
int Level::digCount = Utils::getRand(33, 2);
std::string Level::levelName = "容易难度";

void Level::setLevel(int levelNumber)
{
    levelNum = levelNumber;
    switch (levelNum)
    {
    case 2:
        digCount = Utils::getRand(37, 2);
        levelName = "buttonModeNormal";
        break;
    case 3:
        digCount = Utils::getRand(42, 2);
        levelName = "buttonModeHard";
        break;
    case 4:
        digCount = Utils::getRand(47, 2);
        levelName = "buttonModeHell";
        break;
    default:
        digCount = Utils::getRand(32, 2);
        levelName = "buttonModeEasy";
        break;
    }
}
