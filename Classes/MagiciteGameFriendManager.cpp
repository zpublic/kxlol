#include "MagiciteGameFriendManager.h"

MagiciteGameMoveAbleLiving* MagiciteGameFriendManager::createFriend(Friend_Type type, bool is_to_left/* = false*/)
{
    MagiciteGameMoveAbleLiving* ptr = nullptr;
    switch (type)
    {
    case MagiciteGameFriendManager::Human:
        ptr = MagiciteGameHuman::create();
        if (ptr != nullptr)
        {
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
            auto human = reinterpret_cast<MagiciteGameMoveAbleLiving*>(ptr);
            human->setDire(is_to_left ? MagiciteGameMoveAbleLiving::Direction::left : MagiciteGameMoveAbleLiving::Direction::right);
            return ptr;
        }
        break;
    case MagiciteGameFriendManager::Slime:
        ptr = MagiciteGameSlime::create();
        if (ptr != nullptr)
        {
            ptr->_is_friend = true;
            auto slime = reinterpret_cast<MagiciteGameMoveAbleLiving*>(ptr);
            slime->setDire(is_to_left ? MagiciteGameMoveAbleLiving::Direction::left : MagiciteGameMoveAbleLiving::Direction::right);
            return ptr;
        }
        break;
    case MagiciteGameFriendManager::Sheep:
        ptr = MagiciteGameSheep::create();
        if (ptr != nullptr)
        {
            ptr->_is_friend = true;
            auto slime = reinterpret_cast<MagiciteGameMoveAbleLiving*>(ptr);
            slime->setDire(is_to_left ? MagiciteGameMoveAbleLiving::Direction::left : MagiciteGameMoveAbleLiving::Direction::right);
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
    living->Dead();
}
