#include "MagiciteGameSlime.h"

USING_NS_CC;

MagiciteGameSlime::MagiciteGameSlime()
:MagiciteGameMoveAbleLiving(Slime_Type)
{
    _health_point = slime_hp;
    _mana_point = slime_mp;
}

void MagiciteGameSlime::useSkill(int skillId)
{

}

void MagiciteGameSlime::useSkillEx()
{

}

void MagiciteGameSlime::initAnimation()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img\\Magicite\\slime\\slime.plist", "img\\Magicite\\slime\\slime.png");
}

bool MagiciteGameSlime::init()
{
    if (!MagiciteGameMoveAbleLiving::initWithFile("img\\Magicite\\slime\\slime_stop.png"))
    {
        return false;
    }
    return true;
}

RepeatForever* MagiciteGameSlime::createAnimateJump()
{
    auto act = createAnimateMove();
    act->setTag(AnimationTag::Jump_Tag);
    return act;
}

RepeatForever* MagiciteGameSlime::createAnimateMove()
{
    const char* walkFileName = "slime_walk.png";
    const char* stopFileName = "slime_stop.png";

    Animation* animation = Animation::create();
    SpriteFrame* walkFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(walkFileName);
    animation->addSpriteFrame(walkFrame);
    SpriteFrame* stopFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(stopFileName);
    animation->addSpriteFrame(stopFrame);
    animation->setDelayPerUnit(0.2f);
    animation->setRestoreOriginalFrame(true);

    auto playerAnimation = Animate::create(animation);
    auto action = RepeatForever::create(playerAnimation);
    action->setTag(AnimationTag::Move_Tag);
    return action;
}