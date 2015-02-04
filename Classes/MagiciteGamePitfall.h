#ifndef __MAGICITE_GAME_PITFALL__
#define __MAGICITE_GAME_PITFALL__

#include "cocos2d.h"
#include "MagiciteGamePhySprite.h"

class MagiciteGamePitfallManager;

class MagiciteGamePitfall : public MagiciteGamePhySprite
{
    friend class MagiciteGamePitfallManager;
public:
    MagiciteGamePitfall();
    ~MagiciteGamePitfall();

    virtual bool initWithFile(const char* filename, bool is_turn_on);

    static MagiciteGamePitfall* create(const char* filename, bool is_turn_on);

    bool getPitFallState();
    void setPitFallState(bool is_turn_on);

private:
    bool                            _is_pitfall_on;
};

#endif //__MAGICITE_GAME_PITFALL__