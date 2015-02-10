#ifndef __MAGICITE_GAME_FRIEND_MANAGER__
#define __MAGICITE_GAME_FRIEND_MANAGER__

#include "cocos2d.h"
#include "vector"
#include "MagiciteGameHuman.h"
#include "MagiciteGameChicken.h"
#include "MagiciteGameSlime.h"

class MagiciteGameFriendManager
{
public:
    MagiciteGameFriendManager();

    enum Friend_Type : int
    {
        Human,
        Chicken,
        Slime,
    };

    MagiciteGameMoveAbleLiving* createFriend(Friend_Type type, bool is_to_left = false);
    void destroyFriend(MagiciteGameMoveAbleLiving* living);

    void updateFriendPos();

private:
    std::vector<MagiciteGameMoveAbleLiving*>                _friends;

};

#endif //__MAGICITE_GAME_FRIEND_MANAGER__