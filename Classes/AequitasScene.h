#ifndef __AEQUITAS_SCENE_H__
#define __AEQUITAS_SCENE_H__

#include "cocos2d.h"

class AequitasScene : public cocos2d::Scene
{
public:
    virtual bool init();

    CREATE_FUNC(AequitasScene);
};

#endif // __AEQUITAS_SCENE_H__
