#include "MagiciteGameChicken.h"

USING_NS_CC;

MagiciteGameChicken::MagiciteGameChicken()
:MagiciteGameMoveAbleLiving(Chicken_Type)
{
    _health_point = chicken_hp;
    _mana_point = chicken_mp;
}

void MagiciteGameChicken::useSkill(int skillId)
{

}

void MagiciteGameChicken::useSkillEx()
{

}

void MagiciteGameChicken::initAnimation()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img\\Magicite\\enemy\\chicken.plist", "img\\Magicite\\enemy\\chicken.png");
}

bool MagiciteGameChicken::init()
{
    if (!MagiciteGameMoveAbleLiving::initWithFile("img\\Magicite\\enemy\\chicken_stop.png"))
    {
        return false;
    }
    return true;
}

RepeatForever* MagiciteGameChicken::createAnimateJump()
{
    auto act = createAnimateMove();
    act->setTag(AnimationTag::Jump_Tag);
    return act;
}

RepeatForever* MagiciteGameChicken::createAnimateMove()
{
    const char* walkFileName = "chicken_walk.png";
    const char* stopFileName = "chicken_stop.png";

    Animation* animation = Animation::create();
    SpriteFrame* walkFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(stopFileName);
    animation->addSpriteFrame(walkFrame);
    SpriteFrame* stopFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(walkFileName);
    animation->addSpriteFrame(stopFrame);
    animation->setDelayPerUnit(0.2f);
    animation->setRestoreOriginalFrame(true);

    auto playerAnimation = Animate::create(animation);
    auto action = RepeatForever::create(playerAnimation);
    action->setTag(AnimationTag::Move_Tag);
    return action;
}