#ifndef __MAGICITE_GAME_MOVEABLE_MANAGER__
#define __MAGICITE_GAME_MOVEABLE_MANAGER__

#include <vector>

class MagiciteGameAutoMoveAble;

class MagiciteGameMoveAbleManager
{
public:
    MagiciteGameMoveAbleManager();
    ~MagiciteGameMoveAbleManager();

    void addMoveAble(MagiciteGameAutoMoveAble* obj);
    bool findMoveAble(MagiciteGameAutoMoveAble* obj);
    void eraseMoveAble(MagiciteGameAutoMoveAble* obj);

    void UpdateMoveAble();
private:
    std::vector<MagiciteGameAutoMoveAble*>          _moveables;
};

#endif //__MAGICITE_GAME_MOVEABLE_MANAGER__
