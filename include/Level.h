#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>

class Level
{
public:
    static int levelNum; //数独难度等级
    static int digCount; //数独游戏挖空数
    static std::string levelName; //数独游戏难度名
    static void setLevel(int levelNumber); //设置数独游戏难度
};

#endif //LEVEL_H
