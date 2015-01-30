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
    this->schedule(schedule_selector(MagiciteGameEnemy::update));
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
