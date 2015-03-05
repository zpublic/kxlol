#include "MagiciteGameDirt.h"

USING_NS_CC;

MagiciteGameDirt::MagiciteGameDirt()
:MagiciteGameMoveAbleLiving(Dirt)
{
    _health_point = dirt_hp;
    _mana_point = dirt_mp;
}

void MagiciteGameDirt::initAnimation()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img\\Magicite\\dirt\\dirt.plist", "img\\Magicite\\dirt\\dirt.png");
}

bool MagiciteGameDirt::init()
{
    if (!MagiciteGameMoveAbleLiving::initWithFile("img\\Magicite\\dirt\\dirt_stop.png"))
    {
        return false;
    }
    setSpeed(dirt_speed);

    return true;
}

RepeatForever* MagiciteGameDirt::createAnimateJump()
{
    auto act = createAnimateMove();
    act->setTag(AnimationTag::Jump_Tag);
    return act;
}

RepeatForever* MagiciteGameDirt::createAnimateMove()
{
    const char* walkFileName = "dirt_walk.png";
    const char* stopFileName = "dirt_stop.png";

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
