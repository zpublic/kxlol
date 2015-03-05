#include "MagiciteGameHuman.h"

USING_NS_CC;

MagiciteGameHuman::MagiciteGameHuman()
:MagiciteGameMoveAbleLiving(Human_Type)
{
    _health_point = human_hp;
    _mana_point = human_mp;

}

void MagiciteGameHuman::initAnimation()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img\\Magicite\\player\\player.plist", "img\\Magicite\\player\\player.png");
}

bool MagiciteGameHuman::init()
{
    if (!MagiciteGameMoveAbleLiving::initWithFile("img\\Magicite\\player\\player_stop.png"))
    {
        return false;
    }
    setSpeed(human_speed);

    return true;
}

RepeatForever* MagiciteGameHuman::createAnimateJump()
{
    auto act = createAnimateMove();
    act->setTag(AnimationTag::Jump_Tag);
    return act;
}

RepeatForever* MagiciteGameHuman::createAnimateMove()
{
    const char* walkFileName = "player_walk.png";
    const char* stopFileName = "player_stop.png";

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