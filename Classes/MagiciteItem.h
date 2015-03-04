#ifndef __MAGICITE_ITEM__
#define __MAGICITE_ITEM__

#include "cocos2d.h"

#include "MagiciteGameObject.h"

class MagiciteItem : public MagiciteGameObject
{
public:

    enum ItemType : int
    {
        EffectItem,
        NormalItem,
    };

    ItemType                                _itemType;

    MagiciteItem(ItemType type = NormalItem);
    ~MagiciteItem();

    //MagiciteGameObject
    virtual bool init();
    virtual bool initWithFile(const char* filename);

    std::string getItemName() const;
    int getItemId() const;

    void destroy();

    virtual MagiciteItem* clone() = 0;

    static std::string                      _name;
    static int                              _id;

protected:
    void setItemId(int Id);
    void setItemName(const std::string& name);
};

#endif //__MAGICITE_ITEM__