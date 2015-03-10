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

    void addItem(MagiciteItem* item);
    void eraseItem(int num);

    virtual bool init(int max_size);
    static MagiciteGameBagView* create(int max_size = DEFAULT_MAX_SIZE);

    virtual void onItemUse(int id);

protected:
    float Id2Pos(int n);
    void progressCallback(cocos2d::Node* node);

    cocos2d::Size                                   _size;
    cocos2d::Vec2                                   _origin;
    cocos2d::Node*                                  _cd_node;
    int                                             _bag_blank;
    float                                           _block_size;
    float                                           _offset;
};

#endif //__MAGICITE_GAME_BAG_VIEW__