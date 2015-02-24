#ifndef __MAGICITE_GAME_PLAYER__
#define __MAGICITE_GAME_PLAYER__

#include "cocos2d.h"
#include "MagiciteGameChicken.h"
#include "MagiciteGameHuman.h"
#include "MagiciteGameControlAble.h"
#include "MagiciteEffectSpeedUp.h"
#include "MagiciteEffectJumpHigh.h"
#include "MagiciteEffectSprint.h"

class MagiciteGamePlayer : public MagiciteGameControlAble
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

    void useSkill(MagiciteEffect* effect);

    void Move();
    void Stop();
    void Jump();
    void JumpOver();

    void startAnimation(MagiciteGameMoveAbleLiving::AnimationTag);
    void stopAnimation(MagiciteGameMoveAbleLiving::AnimationTag);

    void setJumpHeight(int offset);
    int getJumpHeight() const;

    void setSpeed(float value);
    float getSpeed() const;

    void setState(MagiciteGameMoveAbleLiving::State state, bool x);
    bool getState(MagiciteGameMoveAbleLiving::State state) const;

    MagiciteGameMoveAbleLiving::Direction getDire() const;
    void setDire(MagiciteGameMoveAbleLiving::Direction dire);

    void setPosition(cocos2d::Vec2 pos);
    cocos2d::Vec2 getPosition() const;

    cocos2d::Size getContentSize() const;
    void setContentSize(cocos2d::Size size);

    void activeSpeedUp();

    void setPetFollow(MagiciteGameObject*);

    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

protected:
    MagiciteGameMoveAbleLiving*             _player;
    bool                                    _move_left;
    bool                                    _move_right;
};

#endif //__MAGICITE_GAME_PLAYER__

