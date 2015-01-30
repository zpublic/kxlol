#ifndef __MAGICITE_GAME_LIVING__
#define __MAGICITE_GAME_LIVING__

#include "Box2D\Box2D.h"
#include "MagiciteGamePhySprite.h"
#include "map"

class MagiciteGameLiving : public MagiciteGamePhySprite
{
public:
    MagiciteGameLiving();
    ~MagiciteGameLiving();

    enum Direction : int
    {
        left = -1,
        right = 1,
    };
    static const int DEFAULT_SPEED = 3;
    static const int DEFAULT_JUMP_HEIGHT = 10;

    virtual void Move(Direction dire);
    virtual void Stop();
    virtual void Jump();
    void setJumpHeight(int offset);
    void setSpeed(int value);

    virtual void useSkill(int skillId);
    virtual void useSkillEx();

    enum State : int
    {
        S_Move,
        S_Jump,
    };
    void setState(State state, bool x);
    bool getState(State state);

    virtual bool initWithFile(const char* filename);
    static MagiciteGameLiving* create(const char* filename);

    enum LivingType : int
    {
        T_Unknow,
        T_Player,
        T_Enemy,
    };
    LivingType                      _LivingType;

protected:
    std::map<State, bool>           _state;
    bool                            _is_to_left;
    int                             _jumpHeight;
    int                             _speed;
};

#endif //__MAGICITE_GAME_LIVING__