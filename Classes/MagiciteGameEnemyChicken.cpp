#include "MagiciteGameEnemyChicken.h"

USING_NS_CC;

MagiciteGameEnemyChicken::MagiciteGameEnemyChicken()
{

}


MagiciteGameEnemyChicken::~MagiciteGameEnemyChicken()
{

}

bool MagiciteGameEnemyChicken::init()
{
    const char* filename = "img\\Magicite\\enemy\\chicken_stop.png";
    if (!MagiciteGameEnemy::initWithFile(filename))
    {
        return false;
    }
    initAnimation();
    return true;
}

void MagiciteGameEnemyChicken::initAnimation()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img\\Magicite\\enemy\\chicken.plist", "img\\Magicite\\enemy\\chicken.png");
}

void MagiciteGameEnemyChicken::startAnimation()
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

void MagiciteGameEnemyChicken::stopAnimation()
{
    if (getState(State::S_ANIMATE))
    {
        this->stopAllActionsByTag(ActionTag::Animate);
        setState(State::S_ANIMATE, false);
    }
}