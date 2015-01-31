#ifndef __MAGICITE_GAME_PLAYER_MANAGER__
#define __MAGICITE_GAME_PLAYER_MANAGER__

#include "MagiciteGamePlayer.h"

class MagiciteGamePlayerManager
{
public:
    static MagiciteGamePlayerManager* getInstance();
    
    MagiciteGamePlayer* getPlayer();

private:
    static MagiciteGamePlayerManager*       _instance;
    MagiciteGamePlayer*                     _player;

    MagiciteGamePlayerManager();
    ~MagiciteGamePlayerManager();
};

#endif //__MAGICITE_GAME_PLAYER_MANAGER__