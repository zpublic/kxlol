#include "MagiciteGamePhySprite.h"

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