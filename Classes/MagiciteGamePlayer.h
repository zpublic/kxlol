#ifndef __MAGICITE_GAME_PLAYER__
#define __MAGICITE_GAME_PLAYER__

#include "cocos2d.h"
#include "MagiciteGameChicken.h"
#include "MagiciteGameHuman.h"

class MagiciteGamePlayer
{
public:
    MagiciteGamePlayer();

    enum PlayerType : int
    {
        Chicken_Type,
        Human_Type,
    };
    typedef  MagiciteGameMoveAbleLiving::Direction      Direction;

    static MagiciteGamePlayer* create(PlayerType type);

    bool init(PlayerType type);

    MagiciteGameMoveAbleLiving* getSprite();

    void useSkill(int skillId);
    void useSkillEx();

    void Move(MagiciteGameMoveAbleLiving::Direction dire);
    void Stop();
    void Jump();
    void JumpOver();

    void startAnimation(MagiciteGameMoveAbleLiving::AnimationTag);
    void stopAnimation(MagiciteGameMoveAbleLiving::AnimationTag);

    void setJumpHeight(int offset);
    int getJumpHeight() const;

    void setSpeed(int value);
    int getSpeed() const;

    void setState(MagiciteGameMoveAbleLiving::State state, bool x);
    bool getState(MagiciteGameMoveAbleLiving::State state) const;

    void setPosition(cocos2d::Vec2 pos);
    cocos2d::Vec2 getPosition() const;

    cocos2d::Size getContentSize() const;
    void setContentSize(cocos2d::Size size);

protected:
    MagiciteGameMoveAbleLiving*             _player;
};

#endif //__MAGICITE_GAME_PLAYER__

