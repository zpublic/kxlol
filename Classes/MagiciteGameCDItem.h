#ifndef __MAGICITE_GAME_CD_ITEM__
#define __MAGICITE_GAME_CD_ITEM__

#include "cocos2d.h"
class MagiciteItem;

class MagiciteGameCDItem : public cocos2d::MenuItem
{
public:
    MagiciteGameCDItem();
    ~MagiciteGameCDItem();


    void setItemView(MagiciteItem*);
    void eraseItemView();

    virtual void activate();
    virtual bool init();

    void startCd(float n);

    CREATE_FUNC(MagiciteGameCDItem);

    void setCD(float n);
    float getCD() const;

    void setCDEnable(bool state);
    bool getCdEnable() const;

protected:
    MagiciteItem*                       _itemView;
    cocos2d::ProgressTimer*             _cdView;
    float                               _cd;
    bool                                _is_cd;
};

#endif //__MAGICITE_GAME_CD_ITEM__