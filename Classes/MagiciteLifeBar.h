#ifndef __MAGICITE_LIFE_BAR__
#define __MAGICITE_LIFE_BAR__

#include "cocos2d.h"

class MagiciteLifeBar : public cocos2d::Node
{
public:
    MagiciteLifeBar();
    ~MagiciteLifeBar();

    void attact(int damage = 1);

    virtual bool init(int max_life, const cocos2d::Size& size);

    static MagiciteLifeBar* create(int max_life, const cocos2d::Size& size);

protected:
    int                                 _max_life;
    int                                 _life;
    float                               _seed;
    cocos2d::Sprite*                    _red;
};

#endif //__MAGICITE_LIFE_BAR__