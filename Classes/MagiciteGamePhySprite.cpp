#include "MagiciteGamePhySprite.h"

MagiciteGamePhySprite::MagiciteGamePhySprite()
:_body(nullptr), _is_dead(false)
{

}

MagiciteGamePhySprite::~MagiciteGamePhySprite()
{

}

b2Body* MagiciteGamePhySprite::getBody() const
{
    return _body;
}

void MagiciteGamePhySprite::setBody(b2Body* body)
{
    _body = body;
}

MagiciteGamePhySprite* MagiciteGamePhySprite::create(const char* filename)
{
    auto ptr = new MagiciteGamePhySprite();
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

bool MagiciteGamePhySprite::initWithFile(const char* filename)
{
    if (!Sprite::initWithFile(filename))
    {
        return false;
    }
    return true;
}

bool MagiciteGamePhySprite::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    return true;
}

bool MagiciteGamePhySprite::isDead() const
{
    return _is_dead;
}

void MagiciteGamePhySprite::Dead()
{
    _is_dead = true;
}