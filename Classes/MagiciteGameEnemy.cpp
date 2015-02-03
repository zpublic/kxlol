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
    initAnimation();
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

void MagiciteGameEnemy::initAnimation()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img\\Magicite\\enemy\\chicken.plist", "img\\Magicite\\enemy\\chicken.png");
}

void MagiciteGameEnemy::startAnimation()
{
    if (!getState(State::S_ANIMATE))
    {
        auto walkFileName = "chicken_walk.png";
        auto stopFileName = "chicken_stop.png";
        Animation* animation = Animation::create();
        SpriteFrame* walkFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(stopFileName);
        animation->addSpriteFrame(walkFrame);
        SpriteFrame* stopFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(walkFileName);
        animation->addSpriteFrame(stopFrame);
        animation->setDelayPerUnit(0.2f);
        animation->setRestoreOriginalFrame(true);

        auto enemyAnimation = Animate::create(animation);
        auto action = RepeatForever::create(enemyAnimation);
        action->setTag(ActionTag::Animate);
        this->runAction(action);
        setState(State::S_ANIMATE, true);
    }
}

void MagiciteGameEnemy::stopAnimation()
{
    if (getState(State::S_ANIMATE))
    {
        this->stopAllActionsByTag(ActionTag::Animate);
        setState(State::S_ANIMATE, false);
    }
}