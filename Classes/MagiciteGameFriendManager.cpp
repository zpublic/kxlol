#include "MagiciteGameFriendManager.h"


MagiciteGameFriendManager::MagiciteGameFriendManager()
{

}

MagiciteGameMoveAbleLiving* MagiciteGameFriendManager::createFriend(Friend_Type type, bool is_to_left/* = false*/)
{
    MagiciteGameMoveAbleLiving* ptr = nullptr;
    switch (type)
    {
    case MagiciteGameFriendManager::Human:
        ptr = MagiciteGameHuman::create();
        if (ptr != nullptr)
        {
            _friends.push_back(ptr);
            ptr->_is_friend = true;
            auto human = reinterpret_cast<MagiciteGameMoveAbleLiving*>(ptr);
            human->setDire(is_to_left ? MagiciteGameMoveAbleLiving::Direction::left : MagiciteGameMoveAbleLiving::Direction::right);
            return ptr;
        }
        break;
    case MagiciteGameFriendManager::Chicken:
        ptr = MagiciteGameChicken::create();
        if (ptr != nullptr)
        {
            ptr->_is_friend = true;
            _friends.push_back(ptr);
            auto human = reinterpret_cast<MagiciteGameMoveAbleLiving*>(ptr);
            human->setDire(is_to_left ? MagiciteGameMoveAbleLiving::Direction::left : MagiciteGameMoveAbleLiving::Direction::right);
            return ptr;
        }
        break;
    default:
        break;
    }
    return nullptr;
}

void MagiciteGameFriendManager::destroyFriend(MagiciteGameMoveAbleLiving* living)
{
    auto iter = std::find(_friends.begin(), _friends.end(), living);
    if (iter != _friends.end())
    {
        (*iter)->Dead();
        _friends.erase(iter);
    }
}

void MagiciteGameFriendManager::updateFriendPos()
{
    for (auto Ptr : _friends)
    {
        auto enemyPtr = Ptr;
        if (enemyPtr->getDire() == MagiciteGameMoveAbleLiving::Direction::left)
        {
            enemyPtr->Move(MagiciteGameMoveAble::left);
        }
        else
        {
            enemyPtr->Move(MagiciteGameMoveAble::right);
        }
    }
}