#include "MagiciteGamePitfallManager.h"

MagiciteGamePitfall* MagiciteGamePitfallManager::createPitfall(Pitfall_Type type, bool is_active /*= true*/)
{
    MagiciteGamePitfall* ptr = nullptr;
    switch (type)
    {
    case Spine_Type:
        ptr = MagiciteGameSpinePitfall::create();
        if (ptr != nullptr)
        {
            ptr->setPitFallAvtive(is_active);
        }
        return ptr;
    default:
        break;
    }
    return nullptr;
}

void MagiciteGamePitfallManager::destroyPitfall(MagiciteGamePitfall* ptr)
{
    ptr->Dead();
}