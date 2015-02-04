#include "MagiciteGamePitfallManager.h"

USING_NS_CC;

MagiciteGamePitfallManager::MagiciteGamePitfallManager()
{

}

MagiciteGamePitfallManager::~MagiciteGamePitfallManager()
{

}

MagiciteGamePitfall* MagiciteGamePitfallManager::createPitfall(
    PitfallType type, 
    Vec2 pos, 
    MagiciteGamePhyLayer* phylayer, 
    bool is_turn_on /* = true */)
{
    MagiciteGamePitfall* pitfall = nullptr;
    switch (type)
    {
    case MagiciteGamePitfallManager::Clamp_Type:
        pitfall = create_and_push(type, pos);
        phylayer->addPhysicSprite(pitfall,true);
        pitfall->setPitFallState(is_turn_on);
        return pitfall;
        break;
    default:
        break;
    }
    return nullptr;
}

void MagiciteGamePitfallManager::destoryPitfall(MagiciteGamePitfall* pitfall)
{
    if (pitfall != nullptr)
    {
        auto pitIter = std::find(_pitfalls.begin(), _pitfalls.end(), pitfall);
        if (pitIter != _pitfalls.end())
        {
            _pitfalls.erase(pitIter);
            pitfall->Dead();
        }
    }
}

MagiciteGamePitfall* MagiciteGamePitfallManager::create_and_push(PitfallType type, cocos2d::Vec2 pos)
{
    auto pitfall = MagiciteGamePitfallClamp::create();
    pitfall->setPosition(pos);
    _pitfalls.push_back(pitfall);

    return pitfall;
}