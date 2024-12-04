#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>

class Level//设置数独的难度类，因为有且仅有唯一Level，所以全部属性、操作均设置为静态，减少Level对象传递的耗时、误操作几率
{
public:
    static int levelNum;//数独游戏难度系数，用于设置Level类属性值
    static int digCount; //数独游戏挖空数，用于生成数独，大致区分不同等级之间的难度
    static std::string levelName; //数独游戏难度名，用于设置GameWindow的labelModeLevel图片源
    static void setLevel(int levelNumber); //设置数独游戏难度，根据传入的难度系数设置属性
};

#endif //LEVEL_H
