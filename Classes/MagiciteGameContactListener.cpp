#include "MagiciteGameContactListener.h"
#include "MagiciteGameContact.h"

USING_NS_CC;

void MagiciteGameContactListener::BeginContact(b2Contact* contact)
{

}

void MagiciteGameContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    if (MagiciteGameContact::_onJudgeContact(contact))
    {
        MagiciteGameContact::_onBeginContact(contact);
    }
    else
    {
        contact->SetEnabled(false);
    }
}

void MagiciteGameContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}

void MagiciteGameContactListener::EndContact(b2Contact* contact)
{

}

MagiciteGameContactListener* MagiciteGameContactListener::create()
{
    auto ptr = new MagiciteGameContactListener();
    if (ptr && ptr->init())
    {
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

bool MagiciteGameContactListener::init()
{
    
    return true;
}
