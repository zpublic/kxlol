#ifndef __MAGICITE_GAME_CONTAINER_VIEW__
#define __MAGICITE_GAME_CONTAINER_VIEW__

#include "MagiciteGameObject.h"
#include <vector>

class MagiciteGameContainerView : public MagiciteGameObject
{
public:
    MagiciteGameContainerView(int n = _max_size);
    ~MagiciteGameContainerView();

    virtual bool init();

    virtual void addItem(MagiciteGameObject* item) = 0;
    virtual void eraseItem(int num) = 0;

protected:
    std::vector<MagiciteGameObject*>                _list;
    static const int                                _max_size = 9;
};

#endif //__MAGICITE_GAME_CONTAINER_VIEW__