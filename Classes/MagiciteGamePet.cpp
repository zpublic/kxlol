#include "MagiciteGamePet.h"

USING_NS_CC;

MagiciteGamePet::MagiciteGamePet()
{

}

bool MagiciteGamePet::init()
{
    if (!MagiciteGameObject::init())
    {
        return false;
    }
    return true;
}

bool MagiciteGamePet::initWithFile(const char* filename)
{
    if (!MagiciteGameObject::initWithFile(filename))
    {
        return false;
    }
    return true;
}

MagiciteGamePet* MagiciteGamePet::create(const char* filename)
{
    auto ptr = new MagiciteGamePet();
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

void MagiciteGamePet::setFloat()
{
    Vector<FiniteTimeAction*> follow;
    follow.pushBack(MoveBy::create(1.0f, Vec2(0.0f, this->getContentSize().height * -2.0f)));
    follow.pushBack(MoveBy::create(1.0f, Vec2(0.0f, this->getContentSize().height * 2.0f)));
    auto repeat = RepeatForever::create(Sequence::create(follow));
    this->runAction(repeat);
}