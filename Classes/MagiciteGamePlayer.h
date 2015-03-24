#ifndef __MAGICITE_GAME_PLAYER__
#define __MAGICITE_GAME_PLAYER__

#include "cocos2d.h"
#include "MagiciteGameControlAble.h"

class MagiciteGameBagView;
class MagiciteEffectItem;
class MagiciteGameMoveAbleLiving;
class MagiciteGamePet;

class MagiciteGamePlayer : public MagiciteGameControlAble
{
public:
    MagiciteGamePlayer();
    ~MagiciteGamePlayer();

    enum PlayerType : int
    {
        Chicken_Type,
        Human_Type,
    };

    static MagiciteGamePlayer* create(MagiciteGameMoveAbleLiving* living);

    bool init(MagiciteGameMoveAbleLiving* living);

    void useItem(MagiciteEffectItem* item);

    void Move();
    void Stop();
    void Jump();
    void JumpOver();

    void setPetFollow(MagiciteGamePet*);

    //MagiciteContralAble
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    MagiciteGameBagView* getBag();
    void useBagItem(int num);
    void switchBagInvisible();

protected:
    MagiciteGameMoveAbleLiving*             _player;
    MagiciteGameBagView*                    _bag;
    bool                                    _move_left;
    bool                                    _move_right;
};

#endif //__MAGICITE_GAME_PLAYER__

