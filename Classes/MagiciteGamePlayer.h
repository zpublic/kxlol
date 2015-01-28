#ifndef __MAGICITE_GAME_PLAYER__
#define __MAGICITE_GAME_PLAYER__

#include "cocos2d.h"
#include "MagiciteGamePhySprite.h"
#define JUMP_EPSINON  0.00001

class MagiciteGamePlayer : public MagiciteGamePhySprite
{
public:
    MagiciteGamePlayer();
    ~MagiciteGamePlayer();

    void playerMove(int offset);
    void playerStop();
    void playerJump();
    void setJumpHeight(int offset);

    virtual bool initWithFile(const char* filename);
    static MagiciteGamePlayer* create(const char* filename);

private:
    bool                _is_to_left;
    int                 _jumpHeight;
};

#endif //__MAGICITE_GAME_PLAYER__

