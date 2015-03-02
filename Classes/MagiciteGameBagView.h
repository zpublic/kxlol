#ifndef __MAGICITE_GAME_BAG_VIEW__
#define __MAGICITE_GAME_BAG_VIEW__

#include "cocos2d.h"
#include "MagiciteGameContainerView.h"

class MagiciteGameBagView : public MagiciteGameContainerView
{
public:
    MagiciteGameBagView();
    ~MagiciteGameBagView();

    virtual bool init();
    virtual void addItem(MagiciteGameObject* item);
    virtual void eraseItem(int num);

    CREATE_FUNC(MagiciteGameBagView);

protected:
    float Id2Pos(int n);

    cocos2d::Size                                   _size;
    cocos2d::Vec2                                   _origin;
    int                                             _bag_blank = 5;
    float                                           _block_size;
    float                                           _offset;
    static const int                                _max_size = 9;
};

#endif //__MAGICITE_GAME_BAG_VIEW__