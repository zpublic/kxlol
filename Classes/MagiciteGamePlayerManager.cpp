#include "MagiciteGamePlayerManager.h"

MagiciteGamePlayerManager* MagiciteGamePlayerManager::_instance = nullptr;

MagiciteGamePlayerManager::MagiciteGamePlayerManager()
:_player(nullptr)
{

}

MagiciteGamePlayerManager::~MagiciteGamePlayerManager()
{

}

MagiciteGamePlayerManager* MagiciteGamePlayerManager::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new MagiciteGamePlayerManager();
    }
    return _instance;
}

MagiciteGamePlayer* MagiciteGamePlayerManager::getPlayer()
{
    if (_player == nullptr)
    {
        _player = MagiciteGamePlayer::create("img\\avatar\\1.png");
    }
    return _player;
}