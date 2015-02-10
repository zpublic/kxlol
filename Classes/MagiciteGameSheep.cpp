#include "MagiciteGameSheep.h"

USING_NS_CC;

MagiciteGameSheep::MagiciteGameSheep()
:MagiciteGameMoveAbleLiving(Sheep_Type)
{
    _health_point = sheep_hp;
    _mana_point = sheep_mp;
}

void MagiciteGameSheep::useSkill(int skillId)
{

}

void MagiciteGameSheep::useSkillEx()
{

}

void MagiciteGameSheep::initAnimation()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img\\Magicite\\sheep\\sheep.plist", "img\\Magicite\\sheep\\sheep.png");
}

bool MagiciteGameSheep::init()
{
    if (!MagiciteGameMoveAbleLiving::initWithFile("img\\Magicite\\sheep\\sheep_stop.png"))
    {
        return false;
    }
    return true;
}


RepeatForever* MagiciteGameSheep::createAnimateJump()
{
    auto act = createAnimateMove();
    act->setTag(AnimationTag::Jump_Tag);
    return act;
}

RepeatForever* MagiciteGameSheep::createAnimateMove()
{
    const char* walkFileName = "sheep_walk.png";
    const char* stopFileName = "sheep_stop.png";

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