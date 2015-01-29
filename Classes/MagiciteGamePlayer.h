#ifndef __MAGICITE_GAME_PLAYER__
#define __MAGICITE_GAME_PLAYER__

#include "cocos2d.h"
#include "MagiciteGamePhySprite.h"
#include "map"

class MagiciteGamePlayer : public MagiciteGamePhySprite
{
public:
    MagiciteGamePlayer();
    ~MagiciteGamePlayer();

    void playerMove(int offset);
    void playerStop();
    void playerJump();
    void setJumpHeight(int offset);

    enum PlayerState : int
    {
        Move,
        Jump,
    };
    void setPlayerState(PlayerState state, bool x);
    bool getPlayerState(PlayerState state);

    virtual bool initWithFile(const char* filename);
    static MagiciteGamePlayer* create(const char* filename);

private:
    std::map<PlayerState,bool>      _state;
    bool                            _is_to_left;
    int                             _jumpHeight;
};

#endif //__MAGICITE_GAME_PLAYER__

