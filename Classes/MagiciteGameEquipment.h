#ifndef _MAGICITE_GAME_EQUIPMENT_H
#define _MAGICITE_GAME_EQUIPMENT_H

#include <cocos2d.h>

class MagiciteGameEquipment : public cocos2d::Node
{
public:
    virtual bool init();

    CREATE_FUNC(MagiciteGameEquipment);

private:
    MagiciteGameEquipment(){}
};

#endif