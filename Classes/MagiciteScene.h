#ifndef __MAGICITE_SCENE_H__
#define __MAGICITE_SCENE_H__

#include "cocos2d.h"
#include "MagiciteGameLayer.h"

class MagiciteScene : public cocos2d::Scene
{
public:
    virtual bool init();
    
    static void setLevel(int level);
    static int getLevel();

    CREATE_FUNC(MagiciteScene);

private:
    static int LevelNumber;
};

#endif // __MAGICITE_SCENE_H__
