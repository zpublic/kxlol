#include "MagiciteGamePlayer.h"

USING_NS_CC;

MagiciteGamePlayer::MagiciteGamePlayer()
{
    _LivingType = MagiciteGameLiving::T_Player;
}

MagiciteGamePlayer::~MagiciteGamePlayer()
{

}

MagiciteGamePlayer* MagiciteGamePlayer::create(const char* filename)
{
    auto ptr = new(std::nothrow) MagiciteGamePlayer();
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

bool MagiciteGamePlayer::initWithFile(const char* filename)
{
    if (!MagiciteGameLiving::initWithFile(filename))
    {
        return false;
    }
    initAnimation();
    return true;
}

void MagiciteGamePlayer::initAnimation()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img\\Magicite\\player\\player.plist", "img\\Magicite\\player\\player.png");
}

void MagiciteGamePlayer::startAnimation()
{
    if (!getState(State::S_ANIMATE))
    {
        auto walkFileName = "player_walk.png";
        auto stopFileName = "player_stop.png";
        Animation* animation = Animation::create();
        SpriteFrame* walkFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(stopFileName);
        animation->addSpriteFrame(walkFrame);
        SpriteFrame* stopFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(walkFileName);
        animation->addSpriteFrame(stopFrame);
        animation->setDelayPerUnit(0.2f);
        animation->setRestoreOriginalFrame(true);

        auto playerAnimation = Animate::create(animation);
        auto action = RepeatForever::create(playerAnimation);
        action->setTag(ActionTag::Animate);
        this->runAction(action);
        setState(State::S_ANIMATE, true);
    }
}


void MagiciteGamePlayer::stopAnimation()
{
    if (getState(State::S_ANIMATE))
    {
        this->stopAllActionsByTag(ActionTag::Animate);
        setState(State::S_ANIMATE, false);
    }
}