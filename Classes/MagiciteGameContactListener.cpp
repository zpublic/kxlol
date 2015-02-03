#include "MagiciteGameContactListener.h"

USING_NS_CC;

void MagiciteGameContactListener::BeginContact(b2Contact* contact)
{
    _onBeginContact(contact);
}

void MagiciteGameContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}

void MagiciteGameContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}

void MagiciteGameContactListener::EndContact(b2Contact* contact)
{

}

MagiciteGameContactListener* MagiciteGameContactListener::create(const std::function<void(b2Contact* contact)> &f)
{
    auto ptr = new MagiciteGameContactListener();
    if (ptr && ptr->init(f))
    {
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

bool MagiciteGameContactListener::init(const std::function<void(b2Contact* contact)> &f)
{
    _onBeginContact = f;
    return true;
}
