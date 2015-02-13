#ifndef __MAGICITE_GAME_PITFALL__
#define __MAGICITE_GAME_PITFALL__

#include "cocos2d.h"
#include "MagiciteGameObject.h"

class MagiciteGamePitfall : public MagiciteGameObject
{
public:
    enum Type{
        hold,
        Spine,
    }PiffallType;

    MagiciteGamePitfall(Type type = hold);

    virtual bool init();
    virtual bool initWithFile(const char* filename);

    CREATE_FUNC(MagiciteGamePitfall);
    static MagiciteGamePitfall* create(const char* filename);

    bool getPitFallAvtive() const;
    void setPitFallAvtive(bool is_active);

    bool getChangeFlag() const;
    void setChangeFlag(bool flag);

protected:
    bool                                _is_active;
    bool                                _change_flag;
};

#endif //__MAGICITE_GAME_PITFALL__