#ifndef __MAGICITE_GAME_BAG_VIEW__
#define __MAGICITE_GAME_BAG_VIEW__

#include "cocos2d.h"
#include "MagiciteGameContainerView.h"

class MagiciteGameBagView : public MagiciteGameContainerView
{
public:

    enum :int {DEFAULT_MAX_SIZE = 9};

    MagiciteGameBagView();
    ~MagiciteGameBagView();

    virtual void addItem(MagiciteItem* item);
    virtual void eraseItem(int num);

    virtual bool init(MagiciteGameObject* obj, int max_size);
    static MagiciteGameBagView* create(MagiciteGameObject* obj, int max_size = DEFAULT_MAX_SIZE);

protected:
    float Id2Pos(int n);

    cocos2d::Size                                   _size;
    cocos2d::Vec2                                   _origin;
    int                                             _bag_blank;
    float                                           _block_size;
    float                                           _offset;
};

#endif //__MAGICITE_GAME_BAG_VIEW__