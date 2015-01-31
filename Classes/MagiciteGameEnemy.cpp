#include "MagiciteGameEnemy.h"

USING_NS_CC;

MagiciteGameEnemy::MagiciteGameEnemy()
{
    _LivingType = MagiciteGameLiving::T_Enemy;
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

void MagiciteGameEnemy::setMoveTo(float new_x_pos)
{
    _start_x_pos = getPositionX();
    _end_x_pos = new_x_pos;
}