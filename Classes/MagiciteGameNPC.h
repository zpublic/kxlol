#ifndef _MAGICITE_GAME_NPC_H
#define _MAGICITE_GAME_NPC_H

#include "MagiciteGameMoveAbleLiving.h"

class MagiciteGameNPC : public MagiciteGameMoveAbleLiving
{
public:
    MagiciteGameNPC();

    virtual void initAnimation();
    virtual bool init();

    virtual void setNpcName(const std::string& strName);

    CREATE_FUNC(MagiciteGameNPC);
protected:
    cocos2d::RepeatForever* createAnimateJump();
    cocos2d::RepeatForever* createAnimateMove();

private:
    cocos2d::Label* _lblName;
};

#endif