#include "MagiciteGamePitfallManager.h"

USING_NS_CC;

MagiciteGamePitfallManager::MagiciteGamePitfallManager()
{

}

MagiciteGamePitfallManager::~MagiciteGamePitfallManager()
{

}

MagiciteGamePitfall* MagiciteGamePitfallManager::createPitfall(PitfallType type, Vec2 pos)
{
    MagiciteGamePitfall* pitfall = createPitfall(type, pos, true);
    if (pitfall != nullptr)
    {
        return pitfall;
    }
    return nullptr;
}

MagiciteGamePitfall* MagiciteGamePitfallManager::createPitfall(PitfallType type, Vec2 pos, bool is_turn_on)
{
    MagiciteGamePitfall* pitfall = nullptr;
    switch (type)
    {
    case MagiciteGamePitfallManager::Clamp_Type:
        pitfall = MagiciteGamePitfallClamp::create(is_turn_on);
        pitfall->setPosition(pos);
        _pitfalls.push_back(pitfall);
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