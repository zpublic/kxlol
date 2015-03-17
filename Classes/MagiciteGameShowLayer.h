#ifndef __MAGICITE_GAME_SHOW_LAYER__
#define __MAGICITE_GAME_SHOW_LAYER__

#include "cocos2d.h"

class MagiciteGameShowLayer : public cocos2d::Layer
{
public:
    MagiciteGameShowLayer();
    ~MagiciteGameShowLayer();

    virtual bool init(float TimeDelta, const std::string& str);

    static MagiciteGameShowLayer* create(float TimeDelta, const std::string& str);

    void start();

private:
    float                   _timeDelta;
    cocos2d::Label*         _label;
};

#endif //__MAGICITE_GAME_SHOW_LAYER__