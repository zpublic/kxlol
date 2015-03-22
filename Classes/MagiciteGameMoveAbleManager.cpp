#include "MagiciteGameMoveAbleManager.h"
#include "MagiciteGameAutoMoveAble.h"

MagiciteGameMoveAbleManager::MagiciteGameMoveAbleManager()
{

}

MagiciteGameMoveAbleManager::~MagiciteGameMoveAbleManager()
{

}

void MagiciteGameMoveAbleManager::addMoveAble(MagiciteGameAutoMoveAble* obj)
{
    if (obj != nullptr)
    {
        _moveables.push_back(obj);
    }
}

bool MagiciteGameMoveAbleManager::findMoveAble(MagiciteGameAutoMoveAble* obj)
{
    return std::find(_moveables.begin(), _moveables.end(), obj) != _moveables.end();
}

void MagiciteGameMoveAbleManager::eraseMoveAble(MagiciteGameAutoMoveAble* obj)
{
    auto iter = std::find(_moveables.begin(), _moveables.end(), obj);
    if (iter != _moveables.end())
    {
        _moveables.erase(iter);
    }
}

void MagiciteGameMoveAbleManager::UpdateMoveAble()
{
    for (auto &r : _moveables)
    {
        r->AutoMove();
    }
}
