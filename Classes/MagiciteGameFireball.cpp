#include "MagiciteGameFireball.h"

USING_NS_CC;

MagiciteGameFireball::MagiciteGameFireball()
{

}

bool MagiciteGameFireball::init()
{
    if (!MagiciteGameAmmo::initWithFile("img\\Magicite\\Ammo\\fireball0.png"))
    {
        return false;
    }

    setSpeed(5);
    this->initAnimation();
    return true;
}

void MagiciteGameFireball::Move(Direction dire)
{
    setFlippedX(dire == Direction::left);
    setBodyXSpeed(_speed * dire);
    startAnimation(AnimationTag::Move_Tag);
    setState(State::S_Move, true);
}

void MagiciteGameFireball::Stop()
{

}

void MagiciteGameFireball::Jump()
{

}

void MagiciteGameFireball::JumpOver()
{

}

void MagiciteGameFireball::initAnimation()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img\\Magicite\\Ammo\\fireballs.plist", "img\\Magicite\\Ammo\\fireballs.png");
}

void MagiciteGameFireball::startAnimation(AnimationTag tag)
{
    switch (tag)
    {
    case MagiciteGameMoveAble::Move_Tag:
        this->runAction(createMoveAnimation());

        break;
    default:
        break;
    }
    setState(State::S_Animate, true);
}

void MagiciteGameFireball::stopAnimation(AnimationTag tag)
{
    if (getState(S_Animate))
    {
        switch (tag)
        {
        case MagiciteGameMoveAble::Move_Tag:
            this->stopActionByTag(Move_Tag);
            this->setState(S_Animate, false);
            break;
        default:
            break;
        }
    }
}

void MagiciteGameFireball::setBodyXSpeed(float x_speed)
{
    getBody()->SetLinearVelocity(b2Vec2(x_speed, getBody()->GetLinearVelocity().y));
}

RepeatForever* MagiciteGameFireball::createMoveAnimation()
{
    char fileName[255];
    Animation* animation = Animation::create();
    for (int i = 0; i < 9; ++i)
    {
        std::sprintf(fileName, "fireball%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
        animation->addSpriteFrame(spriteFrame);
    }

    animation->setDelayPerUnit(0.2f);
    animation->setRestoreOriginalFrame(true);

    auto playerAnimation = Animate::create(animation);
    auto action = RepeatForever::create(playerAnimation);
    action->setTag(AnimationTag::Move_Tag);
    return action;
}