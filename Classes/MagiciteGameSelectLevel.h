#ifndef __MAGICITE_GAME_SELECT_LEVEL__
#define __MAGICITE_GAME_SELECT_LEVEL__

#include "cocos2d.h"
#include "cocos-ext.h"

class MagiciteGameSelectLevel : public cocos2d::Scene
{
public:
    MagiciteGameSelectLevel();
    ~MagiciteGameSelectLevel();

    static const int itemNum = 20;
    static const int pageNum = 5;
    static const int pageItem = itemNum / pageNum;

    CREATE_FUNC(MagiciteGameSelectLevel);
    
    virtual bool init();
    cocos2d::Layer* getContainerLayer();
    void initTouchDispath();

protected:
    void movePage(int distance);

private:
    cocos2d::extension::ScrollView*         _scroll;
    cocos2d::Point                          _beginPoint;
    cocos2d::Point                          _offset;
    int                                     _curPage;
};

#endif //__MAGICITE_GAME_SELECT_LEVEL__