#ifndef __MAGICITE_ITEM__
#define __MAGICITE_ITEM__

#include "cocos2d.h"
#include "MagiciteItemObject.h"

class MagiciteItem
{
public:
    MagiciteItem();
    ~MagiciteItem();

    std::string getItemName() const;
    void setItemName(const std::string& name);

    virtual MagiciteItemObject* getItemObject();

    void destroy();

protected:
    std::string                     _name;
    
};

#endif //__MAGICITE_ITEM__