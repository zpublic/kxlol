#ifndef __MAGICITE_SCENE_H__
#define __MAGICITE_SCENE_H__

#include "cocos2d.h"
#include "MagiciteGameLayer.h"
#include "MagiciteGameSelectLevel.h"

class MagiciteScene : public cocos2d::Scene
{
public:
    virtual bool init(int level);
    
    static int LevelNumber;

    static MagiciteScene* create(int level);
};

#endif // __MAGICITE_SCENE_H__
