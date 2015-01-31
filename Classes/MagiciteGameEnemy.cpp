#include "MagiciteGameEnemy.h"

USING_NS_CC;

MagiciteGameEnemy::MagiciteGameEnemy()
{
    _LivingType = MagiciteGameLiving::T_Enemy;
    _Move_To_Dire = MagiciteGameLiving::Direction::unknow;
    _is_pass = false;
}

MagiciteGameEnemy::~MagiciteGameEnemy()
{

}

bool MagiciteGameEnemy::initWithFile(const char* filename)
{
    if (!MagiciteGameLiving::initWithFile(filename))
    {
        return false;
    }
    return true;
}

MagiciteGameEnemy* MagiciteGameEnemy::create(const char* filename)
{
    auto ptr = new MagiciteGameEnemy();
    if (ptr && ptr->initWithFile(filename))
    {
        ptr->autorelease();
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

void MagiciteGameEnemy::setMoveDire(MagiciteGameLiving::Direction move_to)
{
    _Move_To_Dire = move_to;
}

MagiciteGameLiving::Direction MagiciteGameEnemy::getMoveDire()
{
    return _Move_To_Dire;
}

bool MagiciteGameEnemy::getPass()
{
    return _is_pass;
}