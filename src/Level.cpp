#include "../include/Level.h"
#include "../include/Utils.h"

//MainWindow窗口的初始静态UI需要Level对象的属性进行赋值，所以先初始化Level属性的值
int Level::levelNum = 1;
int Level::digCount = Utils::getRand(33, 2);
std::string Level::levelName = "buttonModeEasy";

void Level::setLevel(int levelNumber)//根据难度选择按钮返回的整数值，设置难度
{
    levelNum = levelNumber;//记录传入整数值作为Level类属性值
    switch (levelNum)//根据参数设置静态属性值
    {
    case 2:
        digCount = Utils::getRand(37, 2);//更新挖空数
        levelName = "buttonModeNormal";//更新图片源名
        break;
    case 3:
        digCount = Utils::getRand(42, 2);//更新挖空数
        levelName = "buttonModeHard";//更新图片源名
        break;
    case 4:
        digCount = Utils::getRand(47, 2);//更新挖空数
        levelName = "buttonModeHell";//更新图片源名
        break;
    default:
        digCount = Utils::getRand(32, 2);//更新挖空数
        levelName = "buttonModeEasy";//更新图片源名
        break;
    }
}
