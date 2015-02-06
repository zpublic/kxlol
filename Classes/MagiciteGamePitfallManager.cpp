#include "MagiciteGamePitfallManager.h"


MagiciteGamePitfallManager::MagiciteGamePitfallManager()
{

}

MagiciteGamePitfallManager::~MagiciteGamePitfallManager()
{

}

MagiciteGamePitfall* MagiciteGamePitfallManager::createPitfall(Pitfall_Type type, bool is_active /*= true*/)
{
    MagiciteGamePitfall* ptr = nullptr;
    switch (type)
    {
    case Spine_Type:
        ptr = MagiciteGameSpinePitfall::create();
        if (ptr != nullptr)
        {
            _pitfalls.push_back(ptr);
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
    auto iter = std::find(_pitfalls.begin(), _pitfalls.end(), ptr);
    if (iter != _pitfalls.end())
    {
        (*iter)->Dead();
        _pitfalls.erase(iter);
    }
}

void MagiciteGamePitfallManager::updatePitfallAvtive()
{
    for (auto iter : _pitfalls )
    {
        if (iter->getChangeFlag())
        {
            auto bodyptr = iter->getBody();
            if (bodyptr != nullptr)
            {
                bodyptr->SetActive(iter->getPitFallAvtive());
            }
            iter->setChangeFlag(false);
        }
    }
}