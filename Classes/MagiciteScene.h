#ifndef __MAGICITE_SCENE_H__
#define __MAGICITE_SCENE_H__

#include "cocos2d.h"
#include "MagiciteGameLayer.h"
#include "MagiciteGameSelectLevel.h"

class MagiciteScene : public cocos2d::Scene
{
public:
    virtual bool init();
    
    static void setLevel(int level);
    static int getLevel();

    static MagiciteScene* create();

    bool _is_ready;
private:
    static int LevelNumber;
};

#endif // __MAGICITE_SCENE_H__
