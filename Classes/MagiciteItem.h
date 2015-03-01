#ifndef __MAGICITE_ITEM__
#define __MAGICITE_ITEM__

#include "cocos2d.h"

class MagiciteGameObject;

class MagiciteItem
{
public:

    MagiciteItem();
    ~MagiciteItem();

    std::string getItemName() const;
    int getItemId() const;

    virtual MagiciteGameObject* getItemObject();

    void destroy();

    static std::string                      _name;
    static int                              _id;

protected:
    void setItemId(int Id);
    void setItemName(const std::string& name);
    
    int                                     _number;
    bool                                    _overlap;
    
};

#endif //__MAGICITE_ITEM__