#ifndef __MAGICITE_GAME_LIVING__
#define __MAGICITE_GAME_LIVING__

#include "Box2D\Box2D.h"
#include "MagiciteGamePhySprite.h"
#include "map"

class MagiciteGameLivine : public MagiciteGamePhySprite
{
public:
    MagiciteGameLivine();
    ~MagiciteGameLivine();

    enum Direction : int
    {
        left = -1,
        right = 1,
    };
    static const int DEFAULT_SPEED = 3;
    static const int DEFAULT_JUMP_HEIGHT = 10;

    void Move(Direction dire);
    void Stop();
    void Jump();
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
    static MagiciteGameLivine* create(const char* filename);

protected:
    std::map<State, bool>           _state;
    bool                            _is_to_left;
    int                             _jumpHeight;
    int                             _speed;
};

#endif //__MAGICITE_GAME_LIVING__